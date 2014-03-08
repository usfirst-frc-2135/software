// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "BallGate.h"
#include "../Commands/BallGateOpen.h"
#include "../Robotmap.h"
BallGate::BallGate() : Subsystem("BallGate") {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	closeSolenoid = RobotMap::ballGateCloseSolenoid;
	ballDetectLimit = RobotMap::ballGateBallDetectLimit;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	printf( "2135: Ball Gate Constructor\n" );
}
    
void BallGate::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
	SetDefaultCommand(new BallGateOpen());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
void BallGate::BallGateCloseValve() {
	closeSolenoid->Set( closeSolenoid->kForward );
}
void BallGate::BallGateOpenValve() {
	closeSolenoid->Set( closeSolenoid->kReverse );
}
