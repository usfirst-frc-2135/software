// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "Sweeper.h"
#include "../Robotmap.h"
#include "../Commands/SweeperArmRetract.h"
Sweeper::Sweeper() : Subsystem("Sweeper") {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	extendSolenoid = RobotMap::sweeperExtendSolenoid;
	wheelMotor = RobotMap::sweeperWheelMotor;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	printf( "2135: Sweeper Constructor\n" );
}
    
void Sweeper::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
	SetDefaultCommand(new SweeperArmRetract());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
//
//	Sweeper deploy solenoid
//
void Sweeper::SweeperDeploy( void ) 
{
	extendSolenoid->Set( extendSolenoid->kForward );
}
//
//	Sweeper retract solenoid
//
void Sweeper::SweeperRetract( void ) 
{
	extendSolenoid->Set( extendSolenoid->kReverse );
}
//
//	Sweeper motor stop
//
void Sweeper::SweeperOff( void ) 
{
	wheelMotor->Set( 0.0 );
}
//
//	Sweeper motor acquire
//
void Sweeper::SweeperAcquire( void ) 
{
	double speed;
	speed = SmartDashboard::GetNumber( "Sweeper Speed" );
	printf( "Sweeper Speed: %f\n", speed );
	wheelMotor->Set( -speed );
}
//
//	Sweeper motor reject
//
void Sweeper::SweeperReject( void ) 
{
	double speed;
	speed = SmartDashboard::GetNumber("Sweeper Speed");
	printf( "Sweeper Speed: %f\n", speed );
	wheelMotor->Set( speed );
}
