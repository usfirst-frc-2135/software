// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "ShooterGateControl.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

ShooterGateControl::ShooterGateControl(bool openState): Command() {
    m_openState = openState;
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void ShooterGateControl::Initialize() {
	printf("2135: Shoot Gate Control %s - Start\n", (m_openState) ? "OPEN" : "CLOSE");
	Robot::shooter->BallGateDeploy(m_openState);
}

// Called repeatedly when this Command is scheduled to run
void ShooterGateControl::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool ShooterGateControl::IsFinished() {
    return true;
}

// Called once after isFinished returns true
void ShooterGateControl::End() {
	printf("2135: Shoot Gate Control - Ended\n");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterGateControl::Interrupted() {
	printf("2135: Shoot Gate Control - Interrupted\n");
}
