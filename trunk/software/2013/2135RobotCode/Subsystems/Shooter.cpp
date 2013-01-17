#include "Shooter.h"
#include "../Robotmap.h"
#include "../Commands/Shoot.h"

Shooter::Shooter() : Subsystem("Shooter") {
	shooterIntakeMotor = new Victor (PWM_SHOOTER_INTAKE_MOTOR);
	shooterExitMotor = new Victor (PWM_SHOOTER_EXIT_MOTOR);
	shooterIntakeMotor->SetSafetyEnabled( false );
	shooterExitMotor->SetSafetyEnabled( false );
}
    
void Shooter::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand ( new Shoot() );
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Shooter::SetPower( float intakePower, float exitPower ) {
	static	int i = 0;
	float	intakePowerPercent;
	float	exitPowerPercent;

	shooterIntakeMotor->Set( intakePower, 0 );
	shooterExitMotor->Set( exitPower, 0 );
	
	intakePowerPercent = - ( intakePower - 1) / 2 * 100;
	exitPowerPercent = - ( exitPower - 1 ) / 2 * 100;
	
	if ( i++ > 25 ) {i = 0 ;
		printf( "Set shooter power: %6.1f  %6.1f\n", intakePowerPercent, exitPowerPercent );
	}
}
