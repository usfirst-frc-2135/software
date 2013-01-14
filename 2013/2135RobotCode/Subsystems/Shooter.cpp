#include "../Robotmap.h"
#include "WPILib.h"
#include "Shooter.h"
#include "../Commands/Shoot.h"

Shooter::Shooter() : Subsystem("Shooter") {
	shooterIntakeMotor = new Victor (PWM_SHOOTER_INTAKE_MOTOR);
	shooterExitMotor = new Victor (PWM_SHOOTER_EXIT_MOTOR);
}
    
void Shooter::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//	SetDefaultCommand ( new Shoot());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Shooter::SetPower(float intakePower, float exitPower) {
	static int i = 0;

	if ( i++ > 200 ) {i = 0 ;
		printf( "Set shooter power: %6.1f  %6.1f\n", intakePower * 100, exitPower * 100);
	}
	shooterIntakeMotor->Set( intakePower, 0 );
	shooterExitMotor->Set( exitPower, 0 );
}
