/*
 * RobotConfiguration.h
 *
 *  Created on: Jan 13, 2018
 *      Author: Administrator
 */

#ifndef ROBOTCONFIGURATION_H_
#define ROBOTCONFIGURATION_H_
#include <stdlib.h>
#include <string>
#include <map>
#include <vector>

class RobotConfig {

public:
	static RobotConfig*GetInstance();
	bool LoadConfig();
	void DumpConfig();
	std::string GetValueAsString(const std::string& name);
	int GetValueAsInt(const std::string& name);
	bool GetValueAsBool(const std::string& name);

private:
	static RobotConfig* currentConfig;
	RobotConfig();
	virtual ~RobotConfig();

	std::map<std::string, std::string> m_configMap;


};

#endif /* ROBOTCONFIGURATION_H_ */
