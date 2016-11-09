// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "CompressorControl.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

CompressorControl::CompressorControl(bool on): Command() {
    m_on = on;
        // Use requires() here to declare subsystem dependencies
    // eg. requires(chassis);
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::pneumatics.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void CompressorControl::Initialize() {
	printf("2135: Compressor Control - Start\n");
	Robot::pneumatics->CompressorEnable(true);
}

// Called repeatedly when this Command is scheduled to run
void CompressorControl::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool CompressorControl::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void CompressorControl::End() {
	Robot::pneumatics->CompressorEnable(false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CompressorControl::Interrupted() {
	Robot::pneumatics->CompressorEnable(false);
}
