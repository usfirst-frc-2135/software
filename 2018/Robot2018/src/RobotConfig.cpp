/*
 * RobotConfig.cpp
 *
 *  Created on: Jan 13, 2018
 *      Author: Administrator
 */

#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <map>
#include <algorithm>
#include "RobotConfig.h"

RobotConfig* RobotConfig::currentConfig = NULL;
const std::string CONFIGFILENAME = "/home/lvuser/2135_configuration.txt";
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
void trimWhitespace(std::string& line) {
	line.erase(std::remove_if( line.begin(), line.end(), [](char c){ return (c =='\r' || c =='\t' || c == ' ' || c == '\n');}), line.end() );
}

////////////////////////////////////////////////////////////////////////////////
RobotConfig* RobotConfig::GetInstance() {
	if (currentConfig == NULL)
		currentConfig = new RobotConfig();
	return currentConfig;
}


RobotConfig::RobotConfig() {
	printf("2135: Before Config Load\n");
	LoadConfig();
	printf("2135: After Config Load, Before Dump\n");
	DumpConfig();
	printf("2135: After Config Dump\n");
}

bool RobotConfig::LoadConfig() {
	std::string fileName = CONFIGFILENAME;
	std::ifstream configFile(fileName.c_str());
	if (configFile.good() == false)
	{
		printf("2135: No such Config file %s.", fileName.c_str());
		return false;
	}
    m_configMap.clear();

	while (configFile.eof() == false) {
		std::string name;
		std::string valueStr;
		std::string delimiter = "=";
		std::string line;

		while(getline(configFile, line)) {
			name = "";			// Reset
			trimWhitespace(line);
			if(line[0] == '#') {
				printf("2135: Ignoring comment\n");
				continue;
			}
			size_t pos = 0;
			if ((pos = line.find(delimiter)) != std::string::npos) {
				name = line.substr(0, pos);
				trimWhitespace(name);
				line.erase(0, pos + delimiter.length());
				trimWhitespace(line);
				valueStr = line;
			}

			if(!name.empty())
			{
				m_configMap[name] = valueStr;
				printf("2135: Adding to m_configMap: '%s'='%s'\n", name.c_str(), valueStr.c_str());
			}

			if(configFile.bad() == true)
			{
				printf("2135: configFile %s bad", fileName.c_str());
				return false;
			}
		}
	}
	return true;
}

//will return false only if there is no value found or specified (default or from file)
bool RobotConfig::GetValueAsString(const std::string& name, std::string& valueStr, std::string defaultStr/*=""*/)
{
	bool rtnStatus = false;
	valueStr = m_configMap[name];
	if(!valueStr.empty())
	{
		 rtnStatus = true;
	}
	else  // this name was not found in m_configMap, so add it using defaultValue.
	{
		if (!defaultStr.empty())
		{
			valueStr = defaultStr;
			m_configMap[name] = valueStr;
			printf("2135: %s not found in RobotConfig; using default value %s\n", name.c_str(), defaultStr.c_str());
			rtnStatus = true;
		}
		else printf("2135: %s not found in RobotConfig and no default value specified.\n", name.c_str());
	}
	return rtnStatus;
}

//Returns true if successful, puts value in valueInt.
bool RobotConfig::GetValueAsInt(const std::string& name, int& valueInt, int defaultInt/*=DUMMY_DEFAULT_INT*/)
{
	bool rtnStatus = false;
	std::string valueStr = m_configMap[name];
	if(!valueStr.empty())
	{
		valueInt = atoi(valueStr.c_str());  // convert to int
		rtnStatus = true;
	}
	else  // this name is not found in m_configMap, so add it if there is a default specified
	{
		if (defaultInt != DUMMY_DEFAULT_INT)
		{
			valueInt = defaultInt;
			std::string valueStr = std::to_string(defaultInt);
			m_configMap[name] = valueStr;
			printf("2135: %s not found in RobotConfig; using default value %d\n", name.c_str(), defaultInt);
			rtnStatus = true;
		}
		else printf("2135: %s not found in RobotConfig and no default value specified.\n", name.c_str());
	}
	return rtnStatus;
}

//Returns true if given name is found in config map & puts its value in valueBool.
bool RobotConfig::GetValueAsBool(const std::string& name, bool& valueBool, bool defaultBool/*=false*/) // default bool if no default is specified  will be false
{
	bool rtnStatus = false;
	std::string valueStr = m_configMap[name];
	if(!valueStr.empty())
	{
		// Assumes that value string is always lowercase 'true' or '1'.
		if((valueStr == "true") || (valueStr == "1"))
			valueBool = true;
		else valueBool = false;
		rtnStatus = true;
	}
	else  // not found in m_configMap, so use default.
	{
		valueBool = defaultBool;
		std::string defaultStr("false");
		if (defaultBool == true)
			defaultStr = "true";
		m_configMap[name] = defaultStr;
		printf("2135: %s not found in RobotConfig; using default value %d\n", name.c_str(), defaultBool);
		rtnStatus = true;
	}
	return rtnStatus;
}

bool RobotConfig::GetValueAsFloat(const std::string& name, float& valueFloat, float defaultFloat/*=DUMMY_DEFAULT_FLOAT*/)
{
	bool rtnStatus = false;
	std::string valueStr = m_configMap[name];
	if(!valueStr.empty())
	{
		valueFloat = atof(valueStr.c_str());  // convert stored value to float
		rtnStatus = true;
	}
	else
	{
		if (defaultFloat != DUMMY_DEFAULT_FLOAT)
		{
			valueFloat = defaultFloat;
			std::string defaultStr = std::to_string(defaultFloat);
			m_configMap[name] = defaultStr;
			printf("2135: %s not found in RobotConfig; using default value %f\n", name.c_str(), defaultFloat);
			rtnStatus = true;
		}
		else printf("2135: %s not found in RobotConfig and no default value specified\n", name.c_str());
	}

	return rtnStatus;
}

void RobotConfig::DumpConfig()
{
	for (std::map<std::string, std::string>::iterator itr = m_configMap.begin(); itr != m_configMap.end(); itr++)
	{
	    std::cout << itr->first << " = " << itr->second << "\n";
	}

//This is testing the get functions with our dummy file. We can remove this once we are confident with the functions.

/*float valueFloat;
if(GetValueAsFloat("AutonDriveSpeed", valueFloat))
	std::cout<<"Test - AutonDriveSpeed" <<" " <<valueFloat <<"\n";
else printf("AutonDriveSpeed could not get float value.\n");

int valueInt;
if(GetValueAsInt("BlahBlah", valueInt))
	std::cout<<"Test - BlahBlah (as int)" <<" " <<valueInt <<"\n";
else printf("BlahBlah could not get int value.\n");

bool valueBool;
if(GetValueAsBool("BlahBlah", valueBool))
	std::cout<<"Test - BlahBlah (as bool)" <<" " <<valueBool <<"\n";
else printf("BlahBlah could not get bool value.");

if(GetValueAsBool("NatureWalk", valueBool ))
	std::cout<<"Test - NatureWalk" <<" " <<valueBool <<"\n";
else printf("NatureWalk could not get value.");

if(GetValueAsFloat("DeprecatedClimber", valueFloat))
	std::cout<<"Test - DeprecatedClimber" <<" " <<valueFloat <<"\n";
else printf("DeprecatedClimber could not get float value.\n");

if(GetValueAsInt("ThingOne", valueInt))
	std::cout<<"Test - ThingOne" <<" " <<valueInt <<"\n";
else printf("ThingOne could not get int value.\n");

if(GetValueAsInt("ThingTwo", valueInt))
	std::cout<<"Test - ThingTwo" <<" " <<valueInt <<"\n";
else printf("ThingTwo could not get int value.\n");

if(GetValueAsBool("PeopleOut", valueBool))
	std::cout<<"Test - PeopleOut (as bool)" <<" " <<valueBool <<"\n";
else printf("PeopleOut could not get bool value.\n");

std::string valueString;
if(GetValueAsString("PeopleOut", valueString))
	std::cout<<"Test - PeopleOut (as string)" <<" " <<valueString <<"\n";
else printf("PeopleOut (as string) could not get value.\n");

if(GetValueAsFloat("Keyboard", valueFloat, 22.5))
	std::cout<<"Test - Keyboard" << " " <<valueFloat <<"\n";
else printf("Keyboard could not get float value.\n");

// The expected value of Keyboard should be 22.5
if(GetValueAsFloat("Keyboard", valueFloat, 56.7))
	std::cout<<"Test - Keyboard" << " " <<valueFloat <<"\n";
else printf("Keyboard could not get float value.\n");

if(GetValueAsFloat("Mouse", valueFloat))
	std::cout<<"Test - Mouse" << " " <<valueFloat <<"\n";
else printf("Keyboard could not get float value.\n");

if(GetValueAsInt("Fence", valueInt))
	std::cout<<"Test - Fence (as int)" <<" " <<valueInt <<"\n";
else printf("Fence could not get int value.\n");

if(GetValueAsInt("Gate", valueInt, 999999))
	std::cout<<"Test - Gate (int)" <<" " <<valueInt <<"\n";
else printf("Gate could not get int value.\n");

if(GetValueAsBool("Tea", valueBool))
	std::cout<<"Test - Tea (as bool)" <<" " <<valueBool <<"\n";
else printf("Tea could not get bool value.");

if(GetValueAsFloat("Chair",valueFloat, DUMMY_DEFAULT_FLOAT))
	std::cout << "Test - Chair (as float)" << " " << valueFloat << "\n";
else printf("Chair could not get float value.");

if(GetValueAsString("Sweatpants", valueString))
	std::cout<<"Test - Sweatpants (as string)" <<" " <<valueString <<"\n";
else printf("Sweatpants (as string) could not get value.\n");*/

}


RobotConfig::~RobotConfig() {

}
