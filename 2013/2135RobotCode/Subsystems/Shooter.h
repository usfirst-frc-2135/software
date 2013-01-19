///////////////////////////////////////////////////////////////////////////////
//
//	Shooter.h
//
//	Shooter subsystem header file
//
#ifndef SHOOTER_H
#define SHOOTER_H

#include "WPILib.h"

//	Subclass subsystem type

class Shooter: public Subsystem {

private:
	Victor *shooterIntakeMotor;			// Declare shooter motors
	Victor *shooterExitMotor;
	
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	Shooter();
	void InitDefaultCommand();
	void SetPower( float intakePower, float exitPower );
};

#endif
