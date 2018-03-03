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
static const double DUMMY_DEFAULT_DOUBLE = 999999.999999;

class RobotConfig {

public:
	static RobotConfig* GetInstance();
	static RobotConfig* currentConfig; //TODO: Should this be private?
	bool LoadConfig();
	void DumpConfig();
	bool GetValueAsString(const std::string& name, std::string& valueString, std::string defaultValue = "");
	bool GetValueAsInt(const std::string& name, int& valueInt, int defaultInt = DUMMY_DEFAULT_INT);
	bool GetValueAsBool(const std::string& name, bool& valueBool, bool defaultBool = false); // default boolean if no default is specified will be false
	bool GetValueAsFloat(const std::string& name, float& valueFloat, float defaultFloat = DUMMY_DEFAULT_FLOAT);
	bool GetValueAsDouble(const std::string& name, double& valueDouble, double defaultDouble = DUMMY_DEFAULT_DOUBLE);

private:

	RobotConfig();
	virtual ~RobotConfig();

	static void GetConfigFileName(std::string& fileName);

	std::map<std::string, std::string> m_configMap;
};

#endif /* ROBOTCONFIG_H_ */
