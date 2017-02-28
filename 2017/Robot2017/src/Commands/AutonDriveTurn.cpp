// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "AutonDriveTurn.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

AutonDriveTurn::AutonDriveTurn(double angle): Command() {
    m_angle = angle;
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::chassis.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void AutonDriveTurn::Initialize() {
	m_angle = SmartDashboard::GetNumber("DriveHeadingAngle", 0.0);
	Robot::chassis->MoveDriveHeadingDistanceInit(0, m_angle);
	printf("2135: Auton Drive Turn - Start\n");
	printf("!!!!! m_angle = %f\n", m_angle);

}

// Called repeatedly when this Command is scheduled to run
void AutonDriveTurn::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool AutonDriveTurn::IsFinished() {
    return Robot::chassis->MoveDriveHeadingIsPIDAtSetPoint();
}

// Called once after isFinished returns true
void AutonDriveTurn::End() {
	Robot::chassis->MoveDriveHeadingStop();
	printf("2135: Auton Drive Turn - End\n");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonDriveTurn::Interrupted() {
	Robot::chassis->MoveDriveHeadingStop();
	printf("2135: Auton Drive Turn - Interrupted\n");
}
