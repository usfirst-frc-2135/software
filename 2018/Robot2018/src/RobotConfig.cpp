/*
 * RobotConfig.cpp
 *
 *  Created on: Jan 13, 2018
 *      Author: Administrator
 */

#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include "RobotConfig.h"

RobotConfig* RobotConfig::currentConfig = NULL;

//////////////////////////////////////////////////////////

//set up class for second value in map
//TODO output origin of value

const int FROMFILE = 0;
const int FROMDEFAULT = 1;
const int FROMOTHER = 2;

std::string ValueInfo::getValue() {
	return m_Value;
}

/* int ValueInfo::getOrigin() {
	return origin;
} */

bool isOriginFile() {
	if (m_Origin == FROMFILE)
		return true;
	return false;
}

bool isOriginDefault() {
	if (m_Origin == FROMDEFAULT)
		return true;
	return false;
}

bool isOriginOther() {
	if (m_Origin == FROMOTHER)
		return true;
	return false;
}

//////////////////////////////////////////////////////////

RobotConfig* RobotConfig::GetInstance() {
	if (currentConfig == NULL)
		currentConfig = new RobotConfig();
	return currentConfig;
	}


RobotConfig::RobotConfig() {
	// TODO Auto-generated constructor stub
	printf("2135: Before Load\n");
	LoadConfig();
	printf("2135: After Load, Before Dump\n");
	DumpConfig();
	printf("2135: After Dump\n");

}

bool RobotConfig::LoadConfig() {
	std::string fileName = "/home/lvuser/2135_configuration.txt";
	std::ifstream configFile(fileName.c_str());
	if (configFile.good() == false)
	{
		printf("2135: No such Config file %s.", fileName.c_str());
		return false;
	}

	while (configFile.eof() == false) {

		std::string type; //Remove when we rewrite the file.
		std::string name;
		std::string value;

		configFile >> type; //Remove when we rewrite the file.
		configFile >> name;
		configFile >> value;


		if(!name.empty())
		{
			m_configMap[name] = value;
			printf("2135: Adding to m_configMap: '%s'='%s'\n", name.c_str(), value.c_str());
		}

		if(configFile.bad() == true)
		{
			printf("2135: configFile %s bad", fileName.c_str());
			return false;
		}

	}

	return true;
}

//will return false only if there is no value found or specified (default or from file)

bool RobotConfig::GetValueAsString(const std::string name, std::string& valueString, std::string defaultValue/*=""*/)
{
	bool rtnStatus = false;
	ValueInfo& myValueInfo = m_configMap[name];
	valueString = myValueInfo.getValue();
	if(!valueString.empty())
	{
		 rtnStatus = true;
	}
	else
	{
		if (!defaultValue.empty())
		{
			valueString = defaultValue;
			m_configMap[name] = defaultValue;
			printf("ERROR: %s not found in RobotConfig. Using default value %s\n", name.c_str(), defaultValue);
			rtnStatus = true;
		}
		else printf("ERROR: %s not found in RobotConfig. No default value specified\n", name.c_str());
	}
	return rtnStatus;
}

//Returns true if successful, puts value in valueInt.
bool RobotConfig::GetValueAsInt(const std::string name, int& valueInt, int defaultValue/*==-545772002*/)
{
	bool rtnStatus = false;
	ValueInfo& myValueInfo = m_configMap[name];
	std::string valueStr  = myValueInfo.getValue();
	if(!valueStr.empty())
	{
		valueInt = atoi(valueStr.c_str());
		rtnStatus = true;
	}
	else
	{
		if (!(defaultValue == -545772002))
		{
			valueInt = defaultValue;
			m_configMap[name] = defaultValue;
			printf("ERROR: %s not found in RobotConfig. Using default value %d\n", name.c_str(), defaultValue);
			rtnStatus = true;
		}
		else printf("ERROR: %s not found in RobotConfig. No default value specified\n", name.c_str());
	}

	return rtnStatus;
}

//Returns true if given name is found in config map & puts its value in valueBool.
bool RobotConfig::GetValueAsBool(const std::string name, bool& valueBool, bool defaultValue/*=false*/) // default bool if no default is specified  will be false
{
	bool rtnStatus = false;
	ValueInfo& myValueInfo = m_configMap[name];
	std::string valueStr = myValueInfo.getValue();
	if(!valueStr.empty())
	{
		// Assumes that value string is always lowercase.
		if((valueStr == "true") || (valueStr == "1"))
			valueBool = true;
		else valueBool = false;
		rtnStatus = true;
	}
	else
	{
		valueInt = defaultValue;
		m_configMap[name] = defaultValue;
		printf("ERROR: %s not found in RobotConfig. Using default value %d\n", name.c_str(), defaultValue);
		rtnStatus = true;
	}

	return rtnStatus;
}

bool RobotConfig::GetValueAsFloat(const std::string name, float& valueFloat, float defaultValue/*=-545.772002*/)
{
	bool rtnStatus = false;
	ValueInfo& myValueInfo = m_configMap[name];
	std::string valueStr = myValueInfo.getValue();
	if(!valueStr.empty())
	{
		valueFloat = atof(valueStr.c_str());
		rtnStatus = true;
	}
	else
	{
		if (!(defaultValue == -545.772002))
		{
			valueFloat = defaultValue;
			m_configMap[name] = defaultValue;
			printf("ERROR: %s not found in RobotConfig. Using default value %f\n", name.c_str(), defaultValue);
			rtnStatus = true;
		}
		else printf("ERROR: %s not found in RobotConfig. No default value specified\n", name.c_str());
	}

	return rtnStatus;
}

void RobotConfig::DumpConfig()
{
	for (std::map<std::string, std::string>::iterator itr = m_configMap.begin(); itr != m_configMap.end(); itr++)
	{
		ValueInfo myValueInfo = itr->second;
		std::cout << itr->first << " = " << myValueInfo.getValue() << "\n";
										//(Valueinfo)itr->second (just in case above code doesn't work
	}

//This is testing the get functions with our dummy file. We can remove this once we are confident with the functions.

/*float valueFloat;
if(GetValueAsFloat("AutonDriveSpeed", valueFloat))
	std::cout<<"AutonDriveSpeed" <<" " <<valueFloat <<"\n";
else printf("AutonDriveSpeed could not get float value.\n");

int valueInt;
if(GetValueAsInt("BlahBlah", valueInt))
	std::cout<<"BlahBlah (as int)" <<" " <<valueInt <<"\n";
else printf("BlahBlah could not get int value.\n");

bool valueBool;
if(GetValueAsBool("BlahBlah", valueBool))
	std::cout<<"BlahBlah (as bool)" <<" " <<valueBool <<"\n";
else printf("BlahBlah could not get bool value.");

if(GetValueAsBool("NatureWalk", valueBool ))
	std::cout<<"NatureWalk" <<" " <<valueBool <<"\n";
else printf("NatureWalk could not get value.");

if(GetValueAsFloat("DeprecatedClimber", valueFloat))
	std::cout<<"DeprecatedClimber" <<" " <<valueFloat <<"\n";
else printf("DeprecatedClimber could not get float value.\n");

if(GetValueAsInt("ThingOne", valueInt))
	std::cout<<"ThingOne" <<" " <<valueInt <<"\n";
else printf("ThingOne could not get int value.\n");

if(GetValueAsInt("ThingTwo", valueInt))
	std::cout<<"ThingTwo" <<" " <<valueInt <<"\n";
else printf("ThingTwo could not get int value.\n");

if(GetValueAsBool("PeopleOut", valueBool))
	std::cout<<"PeopleOut (as bool)" <<" " <<valueBool <<"\n";
else printf("PeopleOut could not get bool value.\n");

std::string valueString;
if(GetValueAsString("PeopleOut", valueString))
	std::cout<<"PeopleOut (as string)" <<" " <<valueString <<"\n";
else printf("PeopleOut (as string) could not get value.\n");*/
}


RobotConfig::~RobotConfig() {
	// TODO Auto-generated destructor stub
}
