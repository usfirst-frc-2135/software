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

class RobotConfig {

public:
	static RobotConfig* GetInstance();
	bool LoadConfig();
	void DumpConfig();
	bool GetValueAsString(const std::string name, std::string& valueString);
	bool GetValueAsInt(const std::string name, int& valueInt);
	bool GetValueAsBool(const std::string name, bool& valueBool);
	bool GetValueAsFloat(const std::string name, float& valueFloat);

private:
	static RobotConfig* currentConfig;
	RobotConfig();
	virtual ~RobotConfig();

	std::map<std::string, std::string> m_configMap;


};

#endif /* ROBOTCONFIG_H_ */
