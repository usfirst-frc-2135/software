// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "Shooter.h"
#include "../Robotmap.h"
#include "../Commands/ShooterIdle.h"
Shooter::Shooter() : Subsystem("Shooter") {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	triggerSolenoid = RobotMap::shooterTriggerSolenoid;
	retractMotor = RobotMap::shooterRetractMotor;
	retractLimit1 = RobotMap::shooterRetractLimit1;
	retractLimit2 = RobotMap::shooterRetractLimit2;
	retractEncoder = RobotMap::shooterRetractEncoder;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	printf( "2135: Shooter Constructor\n" );
}   
void Shooter::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
	SetDefaultCommand(new ShooterIdle());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
//
//	Energize shooter with motor
//
void Shooter::ShooterReload( double speed ) 
{
	retractMotor->Set( speed );
}
//
void Shooter::ShooterEngage( void )
{
	triggerSolenoid->Set( triggerSolenoid->kForward );
	Robot::chassis->UpdateDistance();
}
//
void Shooter::ShooterDisengage( void )
{
	triggerSolenoid->Set( triggerSolenoid->kReverse );
}
bool Shooter::IsShooterFullBack ( void )
{
	//if ( !retractLimit1->Get() && !retractLimit2->Get()  ) 
	if ( retractLimit1->Get() )
		return(true);
	else 
		return(false);
}
