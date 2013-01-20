///////////////////////////////////////////////////////////////////////////////
//
//	Shooter
//
//	Shooter subsystem definition.
//
#include "../Robotmap.h"
#include "Shooter.h"
#include "../Commands/Shoot.h"
#include "../Commands/ShooterOff.h"

Shooter::Shooter() : Subsystem("Shooter") {
	printf( "2135: Shooter - constructed\n" );
	shooterIntakeMotor = new Victor (PWM_SHOOTER_INTAKE_MOTOR);
	shooterExitMotor = new Victor (PWM_SHOOTER_EXIT_MOTOR);
	shooterIntakeMotor->SetSafetyEnabled( false );
	shooterExitMotor->SetSafetyEnabled( false );
}
    
void Shooter::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand ( new ShooterOff() );
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Shooter::SetPower( float intakeJoystick, float exitJoystick ) {
	static	int i = 0;
	float	intakePower;
	float	exitPower;

	intakePower = - ( intakeJoystick - 1) / 2;
	exitPower = - ( exitJoystick - 1 ) / 2;
	shooterIntakeMotor->Set( intakePower, 0 );
	shooterExitMotor->Set( exitPower, 0 );
	
	if ( i++ > 20 ) {
		i = 0 ;
		printf( "2135: Shooter: Set shooter power: %6.1f  %6.1f\n",
			intakePower * 100, exitPower * 100 );
	}
}
