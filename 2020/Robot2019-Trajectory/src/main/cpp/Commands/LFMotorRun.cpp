// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Commands/LFMotorRun.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

LFMotorRun::LFMotorRun(): frc::Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::lifter.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void LFMotorRun::Initialize() {
    std::printf("2135: LFMotorRun - Init\n");
}

// Called repeatedly when this Command is scheduled to run
void LFMotorRun::Execute() {
    Robot::lifter->DriveWithJoystick(Robot::oi->getDStick());
}

// Make this return true when this Command no longer needs to run execute()
bool LFMotorRun::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void LFMotorRun::End() {
    std::printf("2135: LFMotorRun - End\n");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LFMotorRun::Interrupted() {
    std::printf("2135: LFMotorRun - Interrupted\n");
}
