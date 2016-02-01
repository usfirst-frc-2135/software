// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "ShootJoystick.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

ShootJoystick::ShootJoystick(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(chassis);
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::shooter.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	upJoystickShootSpeed = 0.5;
	lowJoystickShootSpeed = 0.5;
}
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void ShootJoystick::Initialize() {
	double shootYAxis = Robot::oi->getOperatorJoystick()->GetY();
	upJoystickShootSpeed = (0.25 * shootYAxis) + 0.75;
	lowJoystickShootSpeed = (-0.25 * shootYAxis) + 0.75;


}

// Called repeatedly when this Command is scheduled to run
void ShootJoystick::Execute() {
	Robot::shooter->ShootSpeeds(upJoystickShootSpeed, lowJoystickShootSpeed);
	Robot::shooter->setFireSolenoid(true);
}

// Make this return true when this Command no longer needs to run execute()
bool ShootJoystick::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void ShootJoystick::End() {
	Robot::shooter->ShootSpeeds(0,0);
	Robot::shooter->setFireSolenoid(false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShootJoystick::Interrupted() {
	Robot::shooter->ShootSpeeds(0,0);
	Robot::shooter->setFireSolenoid(false);
}
