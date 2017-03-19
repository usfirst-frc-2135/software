// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "ClimberMotorLowControl.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

ClimberMotorLowControl::ClimberMotorLowControl(int direction): Command() {
    m_direction = direction;
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::climber.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void ClimberMotorLowControl::Initialize() {
	const char *strName;

	if (m_direction == Robot::climber->CLIMBER_FORWARD_LOW)
		strName = "Climb";
	else if (m_direction == Robot::climber->CLIMBER_REVERSE_LOW)
		strName = "Descend";
	else
		strName = "Off";
	printf("2135: Climber Motor Low Control %s - Start\n", strName);
}

// Called repeatedly when this Command is scheduled to run
void ClimberMotorLowControl::Execute() {
	Robot::climber->SetMotorLowSpeed(m_direction);
}

// Make this return true when this Command no longer needs to run execute()
bool ClimberMotorLowControl::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void ClimberMotorLowControl::End() {
	printf("2135: Climber Motor Low Control - Ended\n");
		Robot::climber->SetMotorLowSpeed(Robot::climber->CLIMBER_STOP_LOW);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimberMotorLowControl::Interrupted() {
	printf("2135: Climber Motor Low Control - Interrupted\n");
	Robot::climber->SetMotorLowSpeed(Robot::climber->CLIMBER_STOP_LOW);
}
