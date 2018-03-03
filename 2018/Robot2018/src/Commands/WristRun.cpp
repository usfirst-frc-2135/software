// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "WristRun.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

WristRun::WristRun(int position): frc::Command() {
    m_position = position;
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::wrist.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void WristRun::Initialize() {
	std::printf("2135: Wrist Run - Init [%d]\n", m_position);
	Robot::wrist->MoveToPosition(m_position);
}

// Called repeatedly when this Command is scheduled to run
void WristRun::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool WristRun::IsFinished() {
	bool isFinished;

	isFinished = Robot::wrist->MoveToPositionIsFinished();

    return isFinished;
}

// Called once after isFinished returns true
void WristRun::End() {
	std::printf("2135: Wrist Run - End\n");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void WristRun::Interrupted() {
	std::printf("2135: Wrist Run - Interrupted\n");
}
