﻿//
//  cppagent.cpp
//

/*
* Copyright (c) 2008, AMT  The Association For Manufacturing Technology (AMT)
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
#include "stdafx.H"

// #define BOOST_ALL_NO_LIB

#include "sys/stat.h"
#include "fcntl.h"
#include <string>
#include <vector>
#include <map>
#include <stdio.h>
#include <algorithm>

#include "WiringAgent.h"


#include "StdStringFcn.h"
#include "Config.h"
#include "AppEventLog.h"
#include "Logger.h"

#include "agent.hpp"
#include "config.hpp"
#include "version.h"
#include "dlib/revision.h"
#include "ProductVersion.h"
#include "libxml/XmlVersion.h"
#include "versionno.h"
#include "WinSingleton.h" 
//#include "YamlReader.h"  // Dont need


#ifdef _WINDOWS

using namespace std;
class AgentEx : public Agent
{
public:
  AgentEx( )
  { }

protected:
  CProductVersion version;
#ifdef HANDLECALL
  virtual std::string handleCall (ostream & out,
    const string &                          path,
    const key_value_map &                   queries,
    const string &                          call,
    const string &                          device)
#else
  virtual std::string handleExtensionCall (const std::string & call, const std::string & device)
#endif
  {
    if ( call == "version" )
    {
      std::string html;
      std::string v = "<versions><version>" + GetVersionString( );
      ReplaceAll(v, "\n", "</version>\n<version>");
      v = v.substr(0, v.size( ) - std::string("<version>").size( ) );
      v = v + "</versions>";
      OutputDebugString(v.c_str( ) );
      html = version.GenerateVersionTable(v);

      return html;
    }
    else if ( call == "documentation" )
    {
      std::string html = version.GenerateXSLTVersion("<versions><version>" + version.GenerateVersionDocument( ) + "</version></versions>");
      return html;
    }
#ifdef HANDLECALL
    return Agent::handleCall(out, path, queries, call, device);

#else
    return "";
#endif
  }

  std::string GetVersionString ( )
  {
    std::string str;

    str += StdStringFormat("MTConnect Core Agent Version %d.%d.%d.%d - built on " __TIMESTAMP__ "\n",
      AGENT_VERSION_MAJOR, AGENT_VERSION_MINOR, AGENT_VERSION_PATCH, AGENT_VERSION_BUILD);
#ifdef WIN64
    std::string compilearch = "64 bit";
#else
    std::string compilearch = "32 bit";
#endif
    str += StdStringFormat("Wiring Agent Extensions  %s Platform Version %s - built on  " __TIMESTAMP__ "\n", compilearch.c_str( ), STRPRODUCTVER);
    str += StdStringFormat("Wiring Agent MSI Install Version %s  \n", version.GetWiringInstallVersion("C:\\Users\\michalos\\Documents\\GitHub\\Agents\\WiringMTConnectAgent\\WiringSetupX64\\WiringSetupX64.vdproj").c_str( ) );
    str += StdStringFormat("Windows Version : %s\n", version.GetOSDisplayString( ).c_str( ) );
    str += StdStringFormat("Microsoft Visual C++ Version %s\n", version.GetMSVCVersion(_MSC_VER) );

    //		str+=StdStringFormat("Dlib version %d.%d dated %s \n", DLIB_MAJOR_VERSION , DLIB_MINOR_VERSION,DLIB_DATE);
    // str+=StdStringFormat("Dlib version %d.%d\n", 17,47);
    str += StdStringFormat("XML Lib version %s \n", LIBXML_DOTTED_VERSION);
    str += StdStringFormat("Boost libraries not used \n");
    str += StdStringFormat("Wiring Devices = %s\n", GetAllDevices( ).c_str( ) );
    return str;
  }

  // This is here becuase the mDeviceMap variable member of Agent is protected, and its easier to just access here than in CProductVersion
  std::string GetAllDevices ( )
  {
    std::string d;

    for ( std::map<std::string, Device *>::iterator it = mDeviceMap.begin( ); it != mDeviceMap.end( ); it++ )
    {
      if ( it != mDeviceMap.begin( ) ) { d += ","; }
      d += ( *it ).first;
    }
    return d;
  }
};

// Handles Win32 exceptions (C structured exceptions) as C++ typed exceptions
static void trans_func (unsigned int u, EXCEPTION_POINTERS *pExp)
{
  std::stringstream outbuf;

  OutputDebugString(outbuf.str( ).c_str( ) );
  throw std::exception( );
}
#endif


int _tmain (int argc, _TCHAR *argv[])
{
  try
  {
    GLogger.Timestamping( )  = true;
    GLogger.DebugString( )   = "WiringAgent";
    GLogger.OutputConsole( ) = true;
    GLogger.Open(File.ExeDirectory( ) + "Debug.txt");
    GLogger.DebugLevel( ) = 0;
    logFatal("Start Wiring Agent\n");

    //	EventLogger.Register();
#ifdef _WINDOWS
    _set_se_translator(trans_func);         // Handles Win32 exceptions (C structured exceptions) as C++ typed exceptions
    // MICHALOSKI ADDED
    TCHAR buf[1000];
    GetModuleFileName(NULL, buf, 1000);
    std::string path(buf);
    path = path.substr(0, path.find_last_of('\\') + 1);
    SetCurrentDirectory(path.c_str( ) );
#endif

#ifdef SINGLETON
	MTConnectSingleton singleton;
    std::vector<std::string>  filepaths;
    DWORD  pid = singleton.GetPid();
    std::string modulename = singleton.GetModuleName();
    std::string modulepath = singleton.GetModulePath();
    std::string processname  = singleton.ExtractFilename(argv[0]);
    std::vector<DWORD> pids = singleton.GetModules(processname,  filepaths);
	remove((File.ExeDirectory( ) + "MaydayMayday.txt").c_str());

	std::vector<std::string>::iterator it =	std::find(filepaths.begin(), filepaths.end(), modulepath);
	if(it != filepaths.end())
		filepaths.erase(it);  // delete 1 - my running image
	// if another one - bad news
	it =	std::find(filepaths.begin(), filepaths.end(), modulepath);
	if(it != filepaths.end())
	{
				CLogger Mayday;
				Mayday.Timestamping( )  = true;
				Mayday.DebugString( )   = "WiringAgent";
				Mayday.OutputConsole( ) = false;
				Mayday.Open(File.ExeDirectory( ) + "MaydayMayday.txt");
				Mayday.DebugLevel( ) = 5;
				Mayday.Fatal("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
				Mayday.Fatal("Conflict with another MTConnect agent with same exe name and http port number\n");
				Mayday.Fatal("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
				Mayday.Close();

	}
#endif
	// This is uncessary, as two exe with same image, must collide.
	// We cannot check if two agents collide on same http port, also bad.
#if 0
	if(filepaths.size() > 1) // should always be one
	{
		YamlReader  yaml;
		std::string exefolder = singleton.ExtractDirectory(modulepath);
		std::string filename = exefolder + "\\Agent.cfg";
		yaml.LoadFromFile(filename);
		std::string portnum = yaml.Find("GLOBAL.Port");

		for(size_t i=0; i< filepaths.size(); i++)
		{
			if(pids[i] == pid)
				continue;
			std::string exefolder = singleton.ExtractDirectory(filepaths[i]);
			filename = exefolder + "\\Agent.cfg";
			yaml.LoadFromFile(filename);
			std::string portnum2 = yaml.Find("GLOBAL.Port");
			if(portnum==portnum2)
			{
				CLogger Mayday;
				Mayday.Timestamping( )  = true;
				Mayday.DebugString( )   = "WiringAgent";
				Mayday.OutputConsole( ) = false;
				Mayday.Open(File.ExeDirectory( ) + "MaydayMayday.txt");
				Mayday.DebugLevel( ) = 5;
				Mayday.Fatal("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
				Mayday.Fatal("Conflict with another MTConnect agent with same exe name and http port number\n");
				Mayday.Fatal("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
				Mayday.Close();
			}

		}
	}
#endif

    AgentConfigurationEx config;
    config.setAgent(new AgentEx( ) );
    Globals.Debug = 0;
    return config.main(argc, (const char **) argv);
  }
  catch ( ... )
  {
    logFatal("Abnormal exception end to  Wiring Agent\n");
  }
  return 0;
}
