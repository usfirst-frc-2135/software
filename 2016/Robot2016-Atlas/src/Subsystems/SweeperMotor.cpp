// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "SweeperMotor.h"
#include "../Robotmap.h"
#include "../Commands/SweeperMotorOff.h"
SweeperMotor::SweeperMotor() : Subsystem("SweeperMotor") {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	wheels = RobotMap::sweeperMotorWheels;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	printf( "2135: Sweeper Motor Constructor\n" );
}
    
void SweeperMotor::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
	SetDefaultCommand(new SweeperMotorOff());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
//
//	Sweeper motor acquire
//
void SweeperMotor::Acquire( void ) 
{
	double speed;
#if SMARTDASHBOARD_ENABLE // SmartDashboard::
	speed = SmartDashboard::GetNumber( "Sweeper Speed" );
#else // SmartDashboard::
	speed = 1.0;
#endif // SmartDashboard::

	wheels->Set( speed );
}
//
//	Sweeper motor reject
//
void SweeperMotor::Reject( void ) 
{
	double speed;
#if SMARTDASHBOARD_ENABLE // SmartDashboard::
	speed = SmartDashboard::GetNumber( "Sweeper Speed" );
#else // SmartDashboard::
	speed = 1.0;
#endif // SmartDashboard::
	wheels->Set( -speed );
}
//
//	Sweeper motor reject
//
void SweeperMotor::Off( void ) 
{
	wheels->Set( 0.0 );
}
