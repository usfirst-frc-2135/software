// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "AutonDriveDistance.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

AutonDriveDistance::AutonDriveDistance(double distance): Command() {
    m_distance = distance;

    std::printf("2135: Auton Drive Distance - Constructor %f inches\n", distance);
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::chassis.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void AutonDriveDistance::Initialize() {
	// If distance is less than 0.1 (default is 0.0), then read smartdashboard
	//	auton programs will pass in larger value
	if (fabs(m_distance) < 0.1) {
		m_distance = Robot::LoadPreferencesVariable(AUTON_DRIVEDISTANCE, AUTON_DRIVEDISTANCE_D);
	}

	std::printf("2135: Auton Drive Distance - Initialize: %f inches\n", m_distance);
	Robot::chassis->MoveDriveDistancePIDInit(m_distance);
}

// Called repeatedly when this Command is scheduled to run
void AutonDriveDistance::Execute() {
	Robot::chassis->MoveDriveDistancePIDExecute();
}

// Make this return true when this Command no longer needs to run execute()
bool AutonDriveDistance::IsFinished() {
    return (Robot::chassis->MoveDriveDistanceIsPIDAtSetpoint());
}

// Called once after isFinished returns true
void AutonDriveDistance::End() {
	Robot::chassis->MoveDriveDistancePIDStop();
	std::printf("2135: Auton Drive Distance - End\n");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonDriveDistance::Interrupted() {
	Robot::chassis->MoveDriveDistancePIDStop();
	std::printf("2135: Auton Drive Distance - Interrupted\n");
}
