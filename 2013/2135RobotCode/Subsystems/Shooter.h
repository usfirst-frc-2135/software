#ifndef SHOOTER_H
#define SHOOTER_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Shooter: public Subsystem {

private:
	Victor *shooterIntakeMotor;
	Victor *shooterExitMotor;
	
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	Shooter();
	void InitDefaultCommand();
	void SetPower(float intakePower, float exitPower);
};

#endif
