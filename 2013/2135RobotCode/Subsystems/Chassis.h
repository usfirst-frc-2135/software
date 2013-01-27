///////////////////////////////////////////////////////////////////////////////
//
//	Chassis.h
//
//	Chassis subsystem header file
//
#ifndef CHASSIS_H
#define CHASSIS_H

#include "WPILib.h"

//	Subclass subsystem type

class Chassis: public Subsystem {
	
private:
	RobotDrive *chassisdriveTrain;				// Declare driveTrain a RobotDrive type
	
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	Chassis();
	void InitDefaultCommand();
	void goStraight();
	void driveWithJoystick( Joystick *stick );
};

#endif
