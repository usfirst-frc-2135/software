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

class RobotConfiguration {

public:
	static RobotConfiguration*GetInstance();
	bool LoadConfiguration();
	void DumpConfiguration();

private:
	static RobotConfiguration* ourConfiguration;
	RobotConfiguration();
	virtual ~RobotConfiguration();

	typedef struct boolVector {
		std::string boolName;
		bool boolValue;
	};

	typedef struct intVector {
		std::string intName;
		int intValue;
	};

	typedef struct doubleVector {
		std::string doubleName;
		double doubleValue;
	};

//	std::map<std::string, bool> myBoolMap;
//	std::map<std::string, int> myIntMap;
//	std::map<std::string, double> myDoubleMap;

};

#endif /* ROBOTCONFIGURATION_H_ */
