#include "../Robotmap.h"
#include "WPILib.h"
#include "../Commands/Shoot.h"
#include "Shooter.h"

Shooter::Shooter() : Subsystem("Shooter") {
	Victor topshooter(PWM_SHOOTER_INTAKE_MOTOR);
	Victor bottomshooter(PWM_SHOOTER_EXIT_MOTOR);
}
    
void Shooter::InitDefaultCommand() {
//	SetDefaultCommand ( new Shoot());
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Shooter::SetPower(double topPower, double bottomPower) {
}
