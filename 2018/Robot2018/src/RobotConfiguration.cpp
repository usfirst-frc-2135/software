/*
 * RobotConfiguration.cpp
 *
 *  Created on: Jan 13, 2018
 *      Author: Administrator
 */

#include "RobotConfiguration.h"

#include <iostream>     // std::cout
#include <fstream>      // std::ifstream

RobotConfiguration* RobotConfiguration::ourConfiguration = NULL;

RobotConfiguration* RobotConfiguration::GetInstance() {
	if (ourConfiguration == NULL)
		ourConfiguration = new RobotConfiguration();
	return ourConfiguration;
	}


RobotConfiguration::RobotConfiguration() {
	// TODO Auto-generated constructor stub
	printf("2135: Before Load\n");
	LoadConfiguration();
	printf("2135: After Load, Before Dump");
	DumpConfiguration();
	printf("2135: After Dump\n");

}

bool RobotConfiguration::LoadConfiguration() {
	std::ifstream configurationFile("/home/lvuser/2135_configuration.txt");

	while (configurationFile.eof() == false) {
		std::string type;
		configurationFile>>type;
		std::string name;

		if (type == "bool") {
			printf("2135: bool\n");
			getline(configurationFile, name);
			std::cout << name;
//			configurationFile>>myBoolMap[name];
		}
		else if (type == "double") {
			printf("2135: double\n");
			std::cout << name;
//			configurationFile>>myDoubleMap[name];
		}
		else if (type == "int") {
			printf("2135: int\n");
			std::cout << name;
//			configurationFile>>myIntMap[name];
		}

		if (configurationFile.bad() == true)
			return false;
	}

	return true;
}

void RobotConfiguration::DumpConfiguration() {

/*for (std::map<std::string, bool>::iterator repeat = myBoolMap.begin(); repeat != myBoolMap.end(); repeat++) {
	std::cout<<repeat->first <<" " <<repeat->second <<"\n";
	}

for (std::map<std::string, double>::iterator repeat = myDoubleMap.begin(); repeat != myDoubleMap.end(); repeat++) {
	std::cout<<repeat->first <<" " <<repeat->second <<"\n";
	}

for (std::map<std::string, int>::iterator repeat = myIntMap.begin(); repeat != myIntMap.end(); repeat++) {
	std::cout<<repeat->first <<" " <<repeat->second <<"\n";
	}*/
}


RobotConfiguration::~RobotConfiguration() {
	// TODO Auto-generated destructor stub
}

