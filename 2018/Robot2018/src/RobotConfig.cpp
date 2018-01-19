/*
 * RobotConfig.cpp
 *
 *  Created on: Jan 13, 2018
 *      Author: Administrator
 */

#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <map>
#include "RobotConfig.h"

RobotConfig* RobotConfig::currentConfig = NULL;

//////////////////////////////////////////////////////////

//set up class for second value in map
//TODO output origin of value

const int FROMFILE = 0;
const int FROMDEFAULT = 1;
const int FROMOTHER = 2;

ValueInfo::ValueInfo(std::string& valueString, int origin) {
	m_Value = valueString;
	m_Origin = origin;
}

ValueInfo::ValueInfo() {
	m_Value = "";
	m_Origin = FROMFILE;
}

ValueInfo::ValueInfo (ValueInfo& myCopy) {
	m_Value = myCopy.GetValue();
	m_Origin = myCopy.GetOrigin();
}

std::string ValueInfo::GetValue() {
	return m_Value;
}

void ValueInfo::SetOrigin( int origin) {
	m_Origin = origin;
}

void ValueInfo::SetValue( std::string svalue) {
	m_Value = svalue;
}

std::string ValueInfo::GetOriginAsText() {
	std::string txtOrigin = "";
	if (m_Origin == FROMFILE)
		txtOrigin += " - from roboRIO configFile";
	if (m_Origin == FROMDEFAULT)
			txtOrigin += " - from default";
	if (m_Origin == FROMOTHER)
			txtOrigin += " - from other";
	return txtOrigin;
}

bool ValueInfo::IsOriginFile() {
	if (m_Origin == FROMFILE)
		return true;
	return false;
}

bool ValueInfo::IsOriginDefault() {
	if (m_Origin == FROMDEFAULT)
		return true;
	return false;
}

bool ValueInfo::IsOriginOther() {
	if (m_Origin == FROMOTHER)
		return true;
	return false;
}

int ValueInfo::GetOrigin() { // private function
	return m_Origin;
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

	//TODO m_configMap.clear();

	while (configFile.eof() == false) {

		std::string name;
		std::string value;

		configFile >> name;
		configFile >> value;

		if(!name.empty())
		{
			ValueInfo myValueInfo(value, FROMFILE);
			//m_configMap[name] = myValueInfo;
			//m_configMap.insert({name , myValueInfo});
			//TODO m_configMap.insert(std::pair<std::string, ValueInfo>(name, myValueInfo));
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

bool RobotConfig::GetValueAsString(std::string name, std::string& valueString, std::string defaultValue/*=""*/)
{
	bool rtnStatus = false;
	ValueInfo/*&*/ myValueInfo; //TODO = m_configMap[name];
	valueString = myValueInfo.GetValue();
	if(!valueString.empty())
	{
		 rtnStatus = true;
		 myValueInfo.SetOrigin(FROMFILE);
	}
	else
	{
		if (!defaultValue.empty())
		{
			valueString = defaultValue;
			printf("ERROR: %s not found in RobotConfig. Using default value %s\n", name.c_str(), defaultValue.c_str());
			rtnStatus = true;
			myValueInfo.SetOrigin(FROMDEFAULT);
			myValueInfo.SetValue(defaultValue);
		}
		else printf("ERROR: %s not found in RobotConfig. No default value specified\n", name.c_str());
	}
	return rtnStatus;
}

//Returns true if successful, puts value in valueInt.
bool RobotConfig::GetValueAsInt( std::string name, int& valueInt, int defaultValue/*==-545772002*/)
{
	bool rtnStatus = false;
	ValueInfo/*&*/ myValueInfo; //TODO = m_configMap[name];
	std::string valueStr  = myValueInfo.GetValue();
	if(!valueStr.empty())
	{
		valueInt = atoi(valueStr.c_str());
		rtnStatus = true;
		myValueInfo.SetOrigin(FROMFILE);
	}
	else
	{
		if (!(defaultValue == -545772002))
		{
			valueInt = defaultValue;
			printf("ERROR: %s not found in RobotConfig. Using default value %d\n", name.c_str(), defaultValue);
			rtnStatus = true;
			myValueInfo.SetOrigin(FROMDEFAULT);
			std::string svalue = std::to_string(defaultValue);
			myValueInfo.SetValue(svalue);
		}
		else printf("ERROR: %s not found in RobotConfig. No default value specified\n", name.c_str());
	}

	return rtnStatus;
}

//Returns true if given name is found in config map & puts its value in valueBool.
bool RobotConfig::GetValueAsBool( std::string name, bool& valueBool, bool defaultValue/*=false*/) // default bool if no default is specified  will be false
{
	bool rtnStatus = false;
	ValueInfo/*&*/ myValueInfo; //TODO = m_configMap[name];
	std::string valueStr = myValueInfo.GetValue();
	if(!valueStr.empty())
	{
		// Assumes that value string is always lowercase.
		if((valueStr == "true") || (valueStr == "1"))
			valueBool = true;
		else valueBool = false;
		rtnStatus = true;
		myValueInfo.SetOrigin(FROMFILE);
	}
	else
	{
		valueBool = defaultValue;
		printf("ERROR: %s not found in RobotConfig. Using default value %d\n", name.c_str(), defaultValue);
		rtnStatus = true;
		myValueInfo.SetOrigin(FROMDEFAULT);
		std::string svalue;
		if (defaultValue == true)
			svalue += "true";
		else svalue += "false";
		myValueInfo.SetValue(svalue);
	}

	return rtnStatus;
}

bool RobotConfig::GetValueAsFloat( std::string name, float& valueFloat, float defaultValue/*=-545.772002*/)
{
	bool rtnStatus = false;
	ValueInfo/*&*/ myValueInfo; //TODO = m_configMap[name];
	std::string valueStr = myValueInfo.GetValue();
	if(!valueStr.empty())
	{
		valueFloat = atof(valueStr.c_str());
		rtnStatus = true;
		myValueInfo.SetOrigin(FROMFILE);
	}
	else
	{
		if (!(defaultValue == -545.772002))
		{
			valueFloat = defaultValue;
			printf("ERROR: %s not found in RobotConfig. Using default value %f\n", name.c_str(), defaultValue);
			rtnStatus = true;
			myValueInfo.SetOrigin(FROMDEFAULT);
			std::string svalue = std::to_string(defaultValue);
			myValueInfo.SetValue(svalue);
		}
		else printf("ERROR: %s not found in RobotConfig. No default value specified\n", name.c_str());
	}

	return rtnStatus;
}

void RobotConfig::DumpConfig()
{
	//TODO for (std::map<std::string, ValueInfo>::iterator itr = m_configMap.begin(); itr != m_configMap.end(); itr++)
	//for (auto& element : m_configMap)
	//for (std::pair<std::string, ValueInfo> element : m_configMap)
	//{
		//ValueInfo myValueInfo = (ValueInfo)(itr->second);
		//ValueInfo myValueInfo = element.second;
		//std::cout << element.first << " = " << myValueInfo.GetValue() << " " << myValueInfo.GetOriginAsText() << "\n";
		//std::cout << itr->first << " = " << myValueInfo.GetValue() << " " << myValueInfo.GetOriginAsText() << "\n";
										//(Valueinfo)itr->second (just in case above code doesn't work
//	}

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
