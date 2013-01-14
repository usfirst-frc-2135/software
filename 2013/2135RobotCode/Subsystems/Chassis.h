#ifndef CHASSIS_H
#define CHASSIS_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Chassis: public Subsystem {
	
private:
	RobotDrive *driveTrain;
	
public:
	Chassis();
	void InitDefaultCommand();
	void goStraight();
	void driveWithJoystick( Joystick *stick );
};

#endif
