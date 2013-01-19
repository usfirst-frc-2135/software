///////////////////////////////////////////////////////////////////////////////
//
//	Shooter
//
//	Shooter subsystem definition.
//
#include "../Robotmap.h"
#include "Shooter.h"
#include "../Commands/Shoot.h"

Shooter::Shooter() : Subsystem("Shooter") {
	printf( "2135: Shooter - constructed\n" );
	shooterIntakeMotor = new Victor (PWM_SHOOTER_INTAKE_MOTOR);
	shooterExitMotor = new Victor (PWM_SHOOTER_EXIT_MOTOR);
	shooterIntakeMotor->SetSafetyEnabled( false );
	shooterExitMotor->SetSafetyEnabled( false );
}
    
void Shooter::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand ( new Shoot( 0 ) );
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
	
	if ( i++ > 20 ) {i = 0 ;
		printf( "Set shooter power: %6.1f  %6.1f\n", intakePowerPercent, exitPowerPercent );
	}
}
