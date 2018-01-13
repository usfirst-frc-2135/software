/*
 * RobotPreferences.h
 *
 *  Created on: Jan 13, 2018
 *      Author: Administrator
 */

#ifndef ROBOTPREFERENCES_H_
#define ROBOTPREFERENCES_H_
#include <stdlib.h>

class RobotPreferences {

public:
	static RobotPreferences*GetInstance();

private:
	static RobotPreferences* ourPreferences;
	RobotPreferences();
	virtual ~RobotPreferences();
};

#endif /* ROBOTPREFERENCES_H_ */
