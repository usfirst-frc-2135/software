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
	sweeperSolenoid = RobotMap::sweeperSweeperSolenoid;
	sweeperMotor = RobotMap::sweeperSweeperMotor;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	printf("2135: Sweeper Constructor\n" );
}
    
void Sweeper::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
	SetDefaultCommand(new SweeperMotorOff());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
void Sweeper::DriveSweeperMotorInit(double speed){
	RobotMap::sweeperSweeperMotor->Set(0.0);
}
void Sweeper::DeploySweeper() {
	sweeperSolenoid->Set( sweeperSolenoid->kForward );
}
void Sweeper::RetractSweeper() {
	sweeperSolenoid->Set( sweeperSolenoid->kReverse );
}
void Sweeper::SweeperAquire() {
	double speed;
	speed = SmartDashboard::GetNumber("Sweeper Speed");
	sweeperMotor->Set( -speed );
}
void Sweeper::SweeperReject() {
	double speed;
	speed = SmartDashboard::GetNumber("Sweeper Speed");
	sweeperMotor->Set( speed );
}
void Sweeper::SweeperOff() {
	sweeperMotor->Set( 0.0 );
}
