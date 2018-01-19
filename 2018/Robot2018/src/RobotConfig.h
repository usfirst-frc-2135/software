/*
 * RobotConfig.h
 *
 *  Created on: Jan 13, 2018
 *      Author: Administrator
 */

#ifndef ROBOTCONFIG_H_
#define ROBOTCONFIG_H_
#include <stdlib.h>
#include <string>
#include <map>
#include <vector>

class ValueInfo {

public:
	ValueInfo(std::string& valueString, int origin);
	ValueInfo();
	ValueInfo(ValueInfo& myCopy);
	std::string GetValue();
	void SetOrigin( int origin);
	void SetValue(std::string svalue);
	std::string GetOriginAsText();
	bool IsOriginFile();
	bool IsOriginDefault();
	bool IsOriginOther();

private:
	int GetOrigin();

private:
	std::string m_Value;
	int m_Origin;
};

class RobotConfig {

public:
	static RobotConfig* GetInstance();
	bool LoadConfig();
	void DumpConfig();
	bool GetValueAsString(std::string name, std::string& valueString, std::string defaultValue = "");
	bool GetValueAsInt( std::string name, int& valueInt, int defaultValue = -545772002);
	bool GetValueAsBool( std::string name, bool& valueBool, bool defaultValue = false); // default boolean if no default is specified will be false
	bool GetValueAsFloat( std::string name, float& valueFloat, float defaultValue = -545.772002);

private:
	static RobotConfig* currentConfig;
	RobotConfig();
	virtual ~RobotConfig();

	//std::map<std::string, std::string> m_configMap;
	//TODO std::map<std::string, ValueInfo> m_configMap;

};

#endif /* ROBOTCONFIG_H_ */
