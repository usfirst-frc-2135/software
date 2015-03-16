// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.
#include "HWheel.h"
#include "../RobotMap.h"
#include "../Commands/HWheelIdle.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
HWheel::HWheel() : Subsystem("HWheel") {
	printf("2135: H Wheel init\n");
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	motorHL = RobotMap::hWheelMotorHL;
	motorHR = RobotMap::hWheelMotorHR;
	encoderH = RobotMap::hWheelEncoderH;
	engage = RobotMap::hWheelEngage;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
}
    
void HWheel::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
	SetDefaultCommand(new HWheelIdle());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}
// Put methods for controlling this subsystem
// here. Call these from Commands.

void HWheel::HWheelRun(double speed) {
	motorHL->Set(speed);
	motorHR->Set(speed);
}

void HWheel::HDriveWithJoystick( Joystick *joystick )
{
	motorHL->Set(joystick->GetX());
	motorHR->Set(joystick->GetX());
}