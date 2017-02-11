// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "GearDoorControl.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

GearDoorControl::GearDoorControl(bool doorState): Command() {
    m_doorState = doorState;
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void GearDoorControl::Initialize() {
	printf("2135: Gear Door Control %s - Start\n", (m_doorState) ? "OPEN" : "CLOSE");
	Robot::delivery->DoorClose(m_doorState);
}

// Called repeatedly when this Command is scheduled to run
void GearDoorControl::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool GearDoorControl::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void GearDoorControl::End() {
	printf("2135: Gear Door Control %s - End\n", (m_doorState) ? "OPEN" : "CLOSE");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void GearDoorControl::Interrupted() {
	printf("2135: Gear Door Control %s - Interrupted\n", (m_doorState) ? "OPEN" : "CLOSE");
}
