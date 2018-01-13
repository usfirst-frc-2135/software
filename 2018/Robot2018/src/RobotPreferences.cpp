/*
 * RobotPreferences.cpp
 *
 *  Created on: Jan 13, 2018
 *      Author: Administrator
 */

#include "RobotPreferences.h"
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream

RobotPreferences* RobotPreferences::ourPreferences = NULL;

RobotPreferences* RobotPreferences::GetInstance() {
	if (ourPreferences == NULL)
			ourPreferences = new RobotPreferences();
	return ourPreferences;
	}


RobotPreferences::RobotPreferences() {
	// TODO Auto-generated constructor stub
	std::ifstream preferencesFile("/home/lvuser/2135_preferences.txt");
	std::string firstWord;
	preferencesFile>>firstWord;

	printf("%s\n", firstWord.c_str());

}

RobotPreferences::~RobotPreferences() {
	// TODO Auto-generated destructor stub
}

