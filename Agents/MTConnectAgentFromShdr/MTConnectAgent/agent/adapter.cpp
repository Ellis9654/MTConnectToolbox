/* 
* Copyright (c) 2008, AMT – The Association For Manufacturing Technology (“AMT”)
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * Neither the name of the AMT nor the
*       names of its contributors may be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* DISCLAIMER OF WARRANTY. ALL MTCONNECT MATERIALS AND SPECIFICATIONS PROVIDED
* BY AMT, MTCONNECT OR ANY PARTICIPANT TO YOU OR ANY PARTY ARE PROVIDED "AS IS"
* AND WITHOUT ANY WARRANTY OF ANY KIND. AMT, MTCONNECT, AND EACH OF THEIR
* RESPECTIVE MEMBERS, OFFICERS, DIRECTORS, AFFILIATES, SPONSORS, AND AGENTS
* (COLLECTIVELY, THE "AMT PARTIES") AND PARTICIPANTS MAKE NO REPRESENTATION OR
* WARRANTY OF ANY KIND WHATSOEVER RELATING TO THESE MATERIALS, INCLUDING, WITHOUT
* LIMITATION, ANY EXPRESS OR IMPLIED WARRANTY OF NONINFRINGEMENT,
* MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. 

* LIMITATION OF LIABILITY. IN NO EVENT SHALL AMT, MTCONNECT, ANY OTHER AMT
* PARTY, OR ANY PARTICIPANT BE LIABLE FOR THE COST OF PROCURING SUBSTITUTE GOODS
* OR SERVICES, LOST PROFITS, LOSS OF USE, LOSS OF DATA OR ANY INCIDENTAL,
* CONSEQUENTIAL, INDIRECT, SPECIAL OR PUNITIVE DAMAGES OR OTHER DIRECT DAMAGES,
* WHETHER UNDER CONTRACT, TORT, WARRANTY OR OTHERWISE, ARISING IN ANY WAY OUT OF
* THIS AGREEMENT, USE OR INABILITY TO USE MTCONNECT MATERIALS, WHETHER OR NOT
* SUCH PARTY HAD ADVANCE NOTICE OF THE POSSIBILITY OF SUCH DAMAGES.
*/

#define __STDC_LIMIT_MACROS 1
#include "adapter.hpp"
#include "device.hpp"
#include "dlib/logger.h"
#include "Logger.h"
#include <map>
using namespace std;

static dlib::logger sLogger("input.adapter");

// jlmichaloski added
std::map<std::string, std::string> Adapter::keymapping; 
std::map<std::string, std::string> Adapter::enummapping; 
std::map<std::string , std::map<std::string, std::string>> Adapter::constantdevmapping; 
std::map<std::string , std::map<std::string, std::string> > Adapter::latestdevvalues; 
std::map<std::string , std::map<std::string, std::string> > Adapter::mergevalues; 


std::vector<std::string> Adapter::rpmEntries; 
int  Adapter::nLogUpdates;
int Adapter::bAllFakeSpindle;
std::map<std::string,int> Adapter::bDeviceFakeSpindle;

std::map<std::string, std::vector<std::string>> Adapter::keymultimapping;

#include <algorithm>

/* Adapter public methods */
Adapter::Adapter(const string& device,
	const string& server,
	const unsigned int port,
	int aLegacyTimeout)
	: Connector(server, port, aLegacyTimeout), mDeviceName(device), mRunning(true),
	mDupCheck(false), mAutoAvailable(false), mIgnoreTimestamps(false),
	mGatheringAsset(false), mReconnectInterval(10 * 1000)
{
	lastime=time(0);
}

Adapter::~Adapter()
{
	// Will stop threaded object gracefully Adapter::thread()
	mRunning = false;
	stop();
	wait();
}

void Adapter::setAgent(Agent &aAgent)
{
	mAgent = &aAgent;
	mDevice = mAgent->getDeviceByName(mDeviceName);
	mDevice->addAdapter(this);

	if (mDevice != NULL)
		mAllDevices.push_back(mDevice);
}

void Adapter::addDevice(string &aName)
{
	Device *dev = mAgent->getDeviceByName(aName);
	if (dev != NULL) {
		mAllDevices.push_back(dev);
		dev->addAdapter(this);
	}
}

inline static bool splitKey(string &key, string &dev) 
{
	size_t found = key.find_first_of(':');
	if (found == string::npos) {
		return false;
	} else {
		dev = key;
		dev.erase(found);
		key.erase(0, found + 1);
		return true;
	}
}

inline static void trim(std::string &str)
{
	size_t index = str.find_first_not_of(" \r\t");
	if (index != string::npos && index > 0)
		str.erase(0, index);
	index = str.find_last_not_of(" \r\t");
	if (index != string::npos)
		str.erase(index + 1);
}

/**
* Expected data to parse in SDHR format:
*   Time|Alarm|Code|NativeCode|Severity|State|Description
*   Time|Item|Value
*   Time|Item1|Value1|Item2|Value2...
* 
* Support for assets:
*   Time|@ASSET@|id|type|<...>...</...>
*/
// Use this define to prevent unwanted exceptions
#ifndef CLEANSTORE
#define CLEANSTORE(Y, X, Z) \
	try{ Y = X; }           \
	catch ( ... ) { Y = Z; 
#endif
template<typename NumberType>
NumberType toNumber(std::string data) 
{
	NumberType result = 0;
	std::istringstream stream(data);

	if(data=="UNKNOWN")
		return 0;
	if(stream >> result)
		return result;
	throw std::runtime_error("Bad number conversion");
}
void Adapter::SaveKeyValue(Device *device, std::string &key, std::string &value)
{

	std::map<std::string, std::string > & keyvalues = latestdevvalues[device->getName()];
	// problem need type!
	keyvalues[key]=value;

}
#include <boost/algorithm/string.hpp>
void Adapter::DoMerges(std::string shdrtime)
{
	typedef std::map<std::string , std::map<std::string, std::string> > ::iterator DEVIT;
	// for each device see if there is any merge key/value pairs
	for(DEVIT it = mergevalues.begin(); it!=mergevalues.end(); it++)
	{
		std::string dev=(*it).first;
		Device * device = mAgent->getDeviceByName(dev);

		if(device==NULL)
			continue;

		std::map<std::string, std::string > keyvalues = latestdevvalues[dev];
		std::map<std::string, std::string > merges = mergevalues[dev];

		for(std::map<std::string, std::string >::iterator it= merges.begin(); it!= merges.end(); it++)
		{
			// (*it).first should contain the device.xml name value to store
			std::string s((*it).second); // this is key of key/value pair
			std::vector<std::pair<std::string::const_iterator,std::string::const_iterator> > tokens;
			boost::split(tokens, s, boost::is_any_of(","));

			// Keys should contain: key1, key2, key3 assume type is numeric or no reason. int can be doubles.
			std::vector<std::string> keys;
			for(auto beg=tokens.begin(); beg!=tokens.end();++beg){
				keys.push_back(std::string(beg->first,beg->second) );
				trim(keys.back());
			}

			size_t i=0;
			size_t index=-1;
			double best=-99.;
			double d;
			for(; i< keys.size(); i++)
			{
				if(keyvalues.find(keys[i]) == keyvalues.end())
					continue;
				try
				{
					if(keyvalues[keys[i]]=="UNAVAILABLE")
						d=0;
					else
						d = toNumber<double>(keyvalues[keys[i]]) ;
					if(d>best)
					{
						best=d;
						index=i;
					}
				}
				catch(...)
				{
				}

			}
			if(index<0)
				continue;
			DataItem *dataItem;
			std::string mergekey = (*it).first;
			{
				dataItem = device->getDeviceDataItem(mergekey);    
				dataItem->setDataSource(this);
				if(keyvalues[keys[index]]=="UNAVAILABLE")
					mAgent->addToBuffer(dataItem, "0", shdrtime);

				else
					mAgent->addToBuffer(dataItem, toUpperCase(keyvalues[keys[index]]), shdrtime);
			}
		}
	}
}
void Adapter::DoConstants(std::string shdrtime)
{
	typedef std::map<std::string , std::map<std::string, std::string> > ::iterator DEVIT;
	// for each device see if there is any merge key/value pairs
	for(DEVIT it = constantdevmapping.begin(); it!=constantdevmapping.end(); it++)
	{
		std::string dev=(*it).first;	// name of the device
		if(constantdevmapping[dev].size()== 0)
			continue;

		Device * device = mAgent->getDeviceByName(dev);
		if(device==NULL)
			continue;


		std::map<std::string, std::string > consts = constantdevmapping[dev];
		for(std::map<std::string, std::string >::iterator it= consts.begin(); it!= consts.end(); it++)
		{
			DataItem *dataItem;
			std::string constkey = (*it).first;
			{
				dataItem = device->getDeviceDataItem(constkey);    
				dataItem->setDataSource(this);
				mAgent->addToBuffer(dataItem, toUpperCase((*it).second), shdrtime);
				// check to see if this is the same key as the shdr key if no give it the constant value
			}
		}

	}
}

void Adapter::CheckConstants(Device *device, std::string shdrtime, std::string &key, std::string &value)
{
	// Handle constants if any for this device - EVERY TIME
	if(device && constantdevmapping[device->getName()].size() >0)
	{
		std::map<std::string, std::string > consts = constantdevmapping[device->getName()];
		size_t cnt=0;
		for(std::map<std::string, std::string >::iterator it= consts.begin(); it!= consts.end(); it++)
		{
			DataItem *dataItem;
			std::string constkey = (*it).first;
			if(constkey==key)
			{
				// remap key's value to the constant value 
				value = toUpperCase((*it).second);
				cnt++;
			}
		}
	}
}
void Adapter::CheckAlias(Device *device, std::string &key, std::string &value)
{
	//if(key == "execution")
	//{
	//	DebugBreak();
	//}


	//////////////////////////////
	// Change enumerations
	if(enummapping.find(key+"."+value)!= enummapping.end())
	{
		value=enummapping[key+"."+value];
	}
	// Map  shdr key (e.g., mode) into new key (controllermode) 
	if(keymapping.find(key)!= keymapping.end())
	{
		key=keymapping[key];
	}
	///////////////////////////////////////////////////////////////////
	// this will log all shdr updates to the log file, can get extremely large
	//if(nLogUpdates)
	//	logStatus("Update Tag %s = Value %s\n", key.c_str(), value.c_str());;

}
void Adapter::processData(const string& data)
{
	if (mGatheringAsset)
	{
		if (data == mTerminator)
		{
			mAgent->addAsset(mAssetDevice, mAssetId, mBody.str(), mAssetType, mTime);
			mGatheringAsset = false;
		}
		else
		{
			mBody << data << endl;
		}

		return;
	}

	istringstream toParse(data);
	string key, value, dev;
	Device *device;

	getline(toParse, key, '|');
	string shdrtime = key;


	// If this function is being used as an API, add the current time in
	if (mIgnoreTimestamps || shdrtime.empty()) {
		shdrtime = getCurrentTime(GMT_UV_SEC);
	}

	getline(toParse, key, '|');
	getline(toParse, value, '|');
	//	std::cout << "key=" << key << " value = " << value << std::endl;
	if (splitKey(key, dev)) {
		device = mAgent->getDeviceByName(dev);
	} else {
		device = mDevice;
	}




	// Debugging since life isn't always perfect
//	LOG_THROTTLE(3, Logging::LOG_INFO, "Device=%s Time=%s Key=%s", device->getName().c_str(), shdrtime.c_str(), key.c_str())

	////////////////////////////////////////////////////////////////////////////////
	// Michaloski hack - remap tag names and enumeration values 
	CheckAlias(device, key, value);
	CheckConstants(device, shdrtime, key, value);
	SaveKeyValue(device, key, value);

	// Michaloski hack - fake a spindle in case there is none  
	// This should be in a separate thread but we'll live
	// time was overloaded replaced with shdrtime
	if((bAllFakeSpindle==1 || bDeviceFakeSpindle[device->getName()] == 1) && (difftime( time(0), lastime) > 1.0) )
	{
//		LOG_ONCE(logFatal("Fake Spindle Enabled\n")  );
		// Reset second calculator
		lastime=time(0);

		try {
			// First we sample xyz mode/execution feed as often as we can.
			// We assume xyz will change frequently enough
			DataItem *sRpmDataItem  = device->getDeviceDataItem("Srpm");    
			if(sRpmDataItem==NULL)
				throw(std::string("Null Srpm DeviceDataItem"));

			std::string feed,X, Y, Z, mode,execution;
			DataItem * dExecution =  device->getDeviceDataItem("execution");
			DataItem * dMode =  device->getDeviceDataItem("controllermode");
			DataItem * dXabs =  device->getDeviceDataItem("Xabs");
			DataItem * dYabs =  device->getDeviceDataItem("Yabs");
			DataItem * dZabs =  device->getDeviceDataItem("Zabs");
			DataItem * dFeed =  device->getDeviceDataItem("path_feedratefrt");
			if(dExecution==NULL || dMode==NULL || dFeed==NULL || dXabs==NULL ||
				dXabs==NULL || dYabs==NULL || dZabs==NULL )
				throw(std::string("Null Fake RPM  DeviceDataItem"));

			std::set<string> aFilter ;
			aFilter.insert(dExecution->getId());
			aFilter.insert(dMode->getId());
			aFilter.insert(dXabs->getId());
			aFilter.insert(dYabs->getId());
			aFilter.insert(dZabs->getId());
			aFilter.insert(dFeed->getId());
			ComponentEventPtrArray events;
			mAgent->mLatest.getComponentEvents(events, &aFilter);

			// Dubious error check
			//if(events.size() < 6)
			//	throw(std::string("Bad Number of Fake ComponentEventsPtr"));

			execution = events[0] ->getValue();
			mode = events[1] ->getValue();
			X = events[2] ->getValue();
			Y = events[3] ->getValue();
			Z = events[4] ->getValue();
			feed = events[5] ->getValue();

			// If moving and in auto mode, assume spindle on
			if(	(mode == "AUTOMATIC" ) &&
				(execution ==  "EXECUTING" )&&
				( 
				device->lastFeed!=feed ||
				device->lastX!=X ||
				device->lastY!= Y ||
				device->lastZ!=Z
				)
				)
			{
				// Fixme: this should be some time based calculation
				device->mLag=4; // 3 cycles - 3 seconds
			}
			else
			{
				device->mLag--;
			}

			if(device->mLag<0) 
				device->mLag=0;

			if(device->mLag>0)
			{
				// set spindle speed to fake number
				mAgent->addToBuffer(sRpmDataItem, "99", shdrtime);
			}
			else
			{
				// set spindle speed to zero
				mAgent->addToBuffer(sRpmDataItem, "0", shdrtime);
			}
		}
		catch(std::string & errmsg)
		{
//			logFatal(errmsg.c_str());
		}
		catch(...)
		{

		}
	}

	////////////////////////////////////////////////////////////////////////////////
	if (key == "@ASSET@") {
		string type, rest;
		getline(toParse, type, '|');
		getline(toParse, rest);

		// Chck for an update and parse key value pairs. If only a type 
		// is presented, then assume the remainder is a complete doc.


		// if the rest of the line begins with --multiline--... then 
		// set multiline and accumulate until a completed document is found
		if (rest.find("--multiline--") != rest.npos)
		{
			mAssetDevice = device;
			mGatheringAsset = true;
			mTerminator = rest;
			mTime = shdrtime;
			mAssetType = type;
			mAssetId = value;
			mBody.str("");
			mBody.clear();
		}
		else
		{
			mAgent->addAsset(device, value, rest, type, shdrtime);
		}

		return;
	} 
	else if (key == "@UPDATE_ASSET@")
	{
		string assetId = value;
		AssetChangeList list;
		getline(toParse, key, '|');
		if (key[0] == '<')
		{
			do {
				pair<string,string> kv("xml", key);
				list.push_back(kv);        
			} while (getline(toParse, key, '|'));

		} 
		else
		{
			while (getline(toParse, value, '|'))
			{
				pair<string,string> kv(key, value);
				list.push_back(kv);      

				if (!getline(toParse, key, '|'))
					break;
			} 
		}
		mAgent->updateAsset(device, assetId, list, shdrtime);
		return;
	}


	DataItem *dataItem;
	if (device != NULL) 
	{
		dataItem = device->getDeviceDataItem(key);    

		if (dataItem == NULL)
		{
			sLogger << LWARN << "(" << mDeviceName << ") Could not find data item: " << key <<
				" from line '" << data << "'";
			sLogger << LDEBUG << "Parse '" << toParse << "' String  from line '" << data << "'";
		} 
		else {
			string rest;
			if (dataItem->isCondition() || dataItem->isAlarm() || dataItem->isMessage() ||
				dataItem->isTimeSeries())
			{
				getline(toParse, rest);
				value = value + "|" + rest;
			}

			// Add key->value pairings
			dataItem->setDataSource(this);
			trim(value);


			// Check for duplication
			if (!mDupCheck || !dataItem->isDuplicate(value)) 
			{
				mAgent->addToBuffer(dataItem, toUpperCase(value), shdrtime);
			} 
			else if (mDupCheck)
			{
				//sLogger << LDEBUG << "Dropping duplicate value for " << key << " of " << value;
			}
		}
	} 
	else 
	{
		sLogger << LDEBUG << "Could not find device: " << dev;
	}

	// Look for more key->value pairings in the rest of the data
	while (getline(toParse, key, '|') && getline(toParse, value, '|'))
	{
		if (splitKey(key, dev)) {
			device = mAgent->getDeviceByName(dev);
		} else {
			device = mDevice;
		}
		if (device == NULL) {
			sLogger << LDEBUG << "Could not find device: " << dev;
			continue;
		}

		////////////////////////////////////////////////////////////////////////////////
		// Michaloski hack - if srpm2 is > 0 assign it to Srpm 
		CheckAlias(device, key, value);
		CheckConstants(device, shdrtime, key, value);
		SaveKeyValue(device, key, value);

		dataItem = device->getDeviceDataItem(key);    
		if (dataItem == NULL)
		{
			sLogger << LWARN << "Could not find data item: " << key << " for device " << mDeviceName;
			//sLogger << LDEBUG << "For Parse '" << toParse << "' String  from line '" << data << "'";
		}
		else
		{
			dataItem->setDataSource(this);
			trim(value);
			if (!mDupCheck || !dataItem->isDuplicate(value)) 
			{
				mAgent->addToBuffer(dataItem, toUpperCase(value), shdrtime);

			} 
			else if (mDupCheck)
			{
				//sLogger << LDEBUG << "Dropping duplicate value for " << key << " of " << value;
			}
		}
	}
	DoConstants(shdrtime);
	DoMerges(shdrtime);

}

void Adapter::protocolCommand(const std::string& data)
{
	// Handle initial push of settings for uuid, serial number and manufacturer. 
	// This will override the settings in the device from the xml
	if (data == "* PROBE") {
		string response = mAgent->handleProbe(mDeviceName);
		string probe = "* PROBE LENGTH=";
		probe.append(intToString(response.length()));
		probe.append("\n");
		probe.append(response);
		probe.append("\n");
		mConnection->write(probe.c_str(), probe.length());
	} else {
		size_t index = data.find(':', 2);
		if (index != string::npos)
		{
			// Slice from the second character to the :, without the colon
			string key = data.substr(2, index - 2);
			trim(key);        
			string value = data.substr(index + 1);
			trim(value);

			if (key == "uuid") {
				if (!mDevice->mPreserveUuid) mDevice->setUuid(value);
			} else if (key == "manufacturer")
				mDevice->setManufacturer(value);
			else if (key == "station")
				mDevice->setStation(value);
			else if (key == "serialNumber")
				mDevice->setSerialNumber(value);
			else if (key == "description")
				mDevice->setDescription(value);
			else if (key == "nativeName")
				mDevice->setNativeName(value);
			else
				sLogger << LWARN << "Unknown command '" << data << "' for device '" << mDeviceName;
		}
	}  
}

void Adapter::disconnected()
{
	mAgent->disconnected(this, mAllDevices);
}

void Adapter::connected()
{
	mAgent->connected(this, mAllDevices);
}

/* Adapter private methods */
void Adapter::thread()
{
	while (mRunning)
	{
		try
		{
			// Start the connection to the socket
			connect();

			// make sure we're closed...
			close();
		}
		catch (...)
		{
			sLogger << LERROR << "Thread for adapter " << mDeviceName << "'s thread threw an unhandled exception";
		}

		// Try to reconnect every 10 seconds
		sLogger << LINFO << "Will try to reconnect in " << mReconnectInterval << " milliseconds";
		dlib::sleep(mReconnectInterval);
	}
}

