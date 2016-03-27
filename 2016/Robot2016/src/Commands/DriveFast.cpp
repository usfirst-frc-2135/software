// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "DriveFast.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

DriveFast::DriveFast(bool isForward): Command() {
    m_isForward = isForward;
        // Use requires() here to declare subsystem dependencies
    Requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void DriveFast::Initialize() {
	printf("2135: Drive Fast running\n");
}

// Called repeatedly when this Command is scheduled to run
void DriveFast::Execute() {
	if (m_isForward == true) {
		Robot::chassis->MoveUsingLeftRightMotorOutputs(1.0, 1.0);
	}
	else {
		Robot::chassis->MoveUsingLeftRightMotorOutputs(-1.0, -1.0);
	}

	SmartDashboard::PutNumber("Encoder Rate", Robot::chassis->leftEncoder->GetRate());
}

// Make this return true when this Command no longer needs to run execute()
bool DriveFast::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void DriveFast::End() {
	printf("2135: DriveFast Ended\n");
	Robot::chassis->MoveStop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveFast::Interrupted() {
	printf("2135: DriveFast Interrupted\n");
	Robot::chassis->MoveStop();
}
