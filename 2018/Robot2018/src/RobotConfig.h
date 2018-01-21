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


static const int DUMMY_DEFAULT_INT = 999999;
static const float DUMMY_DEFAULT_FLOAT = 999999.999;

class RobotConfig {

public:
	static RobotConfig* GetInstance();
	bool LoadConfig();
	void DumpConfig();
	bool GetValueAsString(const std::string& name, std::string& valueString, std::string defaultValue = "");
	bool GetValueAsInt(const std::string& name, int& valueInt, int defaultInt = DUMMY_DEFAULT_INT);
	bool GetValueAsBool(const std::string& name, bool& valueBool, bool defaultBool = false); // default boolean if no default is specified will be false
	bool GetValueAsFloat(const std::string& name, float& valueFloat, float defaultFloat = DUMMY_DEFAULT_FLOAT);
	static RobotConfig* currentConfig;

private:
	RobotConfig();
	virtual ~RobotConfig();

	std::map<std::string, std::string> m_configMap;
};

#endif /* ROBOTCONFIG_H_ */
