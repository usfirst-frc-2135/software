// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Commands/LFBackDeploy.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

LFBackDeploy::LFBackDeploy(bool extended): frc::Command() {
    m_extended = extended;
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::lifter.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void LFBackDeploy::Initialize() {
    std::printf("2135: Lifter Back Deploy Init - %s\n", (m_extended) ? "EXTEND" : "RETRACT");
    Robot::lifter->SetBackSolenoid(m_extended);
}

// Called repeatedly when this Command is scheduled to run
void LFBackDeploy::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool LFBackDeploy::IsFinished() {
    return true;
}

// Called once after isFinished returns true
void LFBackDeploy::End() {
    std::printf("2135: Lifter Front Deploy - End\n");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LFBackDeploy::Interrupted() {
    std::printf("2135: Lifter Front Deploy - Interrupted\n");
}
