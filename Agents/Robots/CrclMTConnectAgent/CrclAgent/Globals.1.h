//
// Globals.h
//

// DISCLAIMER:
// This software was developed by U.S. Government employees as part of
// their official duties and is not subject to copyright. No warranty implied 
// or intended.

#pragma once
#include <stdio.h>
#include <vector>
#include <map>
#include <string>

#include "StdStringFcn.h"
#include "Logger.h"
#include "File.h"

class CGlobals
{
public:

	int &Debug;
	int QueryServer;
	int ServerRate;

	std::string inifile;
	std::string CfgFile;
	std::string DevicesFile;
	std::string HttpPort;
	std::string ServerName;

	int ResetAtMidnight;
	int & DbgConsole;
	int Transfer;

	CGlobals() : Debug(GLogger.DebugLevel()), 
		DbgConsole(GLogger.OutputConsole())
	{
		ServerRate=2000;

		inifile=File.ExeDirectory() + "Config.ini";	
		CfgFile=File.ExeDirectory() + "Afgent.cfg";	
		DevicesFile=File.ExeDirectory() + "Devices.xml";	

		GLogger.Timestamp()=true;
		Debug=0;
		QueryServer=10000;
		HttpPort="5000";
		ServerName="CrclAgent";
		ResetAtMidnight=0;
		Transfer=0;
	
	}
	void Dump()
	{
		std::stringstream sstr;
		sstr << "Globals ServerName " << ServerName << std::endl;
		sstr << "Globals HttpPort " << HttpPort << std::endl;
		sstr << "Globals Debug " << Debug << std::endl;
		sstr << "Globals QueryServer " << QueryServer << std::endl;
		sstr << "Globals ServerRate " << ServerRate << std::endl;
		sstr << "Globals ResetAtMidnight " << ResetAtMidnight << std::endl;
		sstr << "Globals Debug View " << DbgConsole << std::endl;
		sstr << "Globals Inifile " << inifile << std::endl;
		sstr << "Globals Cfgfile " << CfgFile << std::endl;
		sstr << "Globals Devicesfile " << DevicesFile << std::endl;
		OutputDebugString(sstr.str().c_str());
	}


};

__declspec(selectany)  CGlobals Globals;

