// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Commands/WRRun.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

WRRun::WRRun(int level): frc::Command() {
    m_level = level;
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::wrist.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void WRRun::Initialize() {
	std::printf("2135: WRRun - Init [%d]\n", m_level);
    Robot::wrist->MoveToPositionInit(m_level);
}

// Called repeatedly when this Command is scheduled to run
void WRRun::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool WRRun::IsFinished() {
    return Robot::wrist->MoveToPositionIsFinished();
}

// Called once after isFinished returns true
void WRRun::End() {
	std::printf("2135: WRRun - End\n");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void WRRun::Interrupted() {
	std::printf("2135: WRRun - Interrupted\n");
}
