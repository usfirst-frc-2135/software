// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "GripperRun.h"
#include "../Subsystems/Gripper.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

GripperRun::GripperRun(bool intakeDirection): frc::Command() {
    m_intakeDirection = intakeDirection;
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::gripper.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void GripperRun::Initialize() {
	std::printf("2135: GripperRun - Init\n");

}

// Called repeatedly when this Command is scheduled to run
void GripperRun::Execute() {
	Robot::gripper->GripperMove(m_intakeDirection);
}

// Make this return true when this Command no longer needs to run execute()
bool GripperRun::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void GripperRun::End() {
	std::printf("2135: GripperRun - End \n");

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void GripperRun::Interrupted() {
	std::printf("2135: GripperRun - Interrupted \n");

}
