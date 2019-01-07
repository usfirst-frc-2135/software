// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Commands/AutoPos1.h"
#include "Commands/AutoPosANYMove.h"
#include "Commands/AutoPos1Switch.h"
#include "Commands/AutoPos1Scale.h"

#include "RobotDefaults.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

AutoPos1::AutoPos1(): frc::Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void AutoPos1::Initialize() {
	std::printf("2135: Auto Pos 1 - Init\n");

}

// Called repeatedly when this Command is scheduled to run
void AutoPos1::Execute() {
	// Wait for gameData before scheduling next steps
}

// Make this return true when this Command no longer needs to run execute()
bool AutoPos1::IsFinished() {
	bool			isFinished = false;
	std::string 	alliSwitch;			// Holds alliance switch game data setting
	std::string 	scale;				// Holds scale game data setting
	frc::Command	* cmd = nullptr;	// Pointer to command/command group to run

	// Check if gameData has been sent
	alliSwitch = frc::SmartDashboard::GetString(ROBOT_FMSALLISWITCH, ROBOT_FMS_UNINIT);
	// If not the uninitialized string, then new data received
	if (alliSwitch.compare(ROBOT_FMS_UNINIT) != 0) {
		bool allowScale;
		allowScale = frc::SmartDashboard::GetBoolean(ROBOT_ALLOW_SCALE, false);

		// Select group command for Pos 1 decisions here
		scale = frc::SmartDashboard::GetString(ROBOT_FMSSCALE, ROBOT_FMS_UNINIT);
		std::printf("2135: Auto Pos 1 - AlliSwitch: %s Scale: %s Dash: %s\n",
				alliSwitch.c_str(), scale.c_str(), (allowScale) ? "TRUE" : "FALSE");

		if (alliSwitch.compare(ROBOT_FMS_RIGHT) == 0) {		// If alliance switch is RIGHT
			if ((scale.compare(ROBOT_FMS_LEFT) == 0) && allowScale) { 	// If scale is LEFT (case RL) and allowed
				cmd = new(AutoPos1Scale);					// Attack the scale
			}
			else if (scale.compare(ROBOT_FMS_RIGHT) == 0) {	// If scale is RIGHT (case RR)
				cmd = new(AutoPosANYMove);					// Drive to auto line
			}
			else {
				std::printf("2135: Auto Pos 1 - unrecognized scale side\n");
				cmd = new(AutoPosANYMove);					// Drive to auto line
			}
		}
		else if (alliSwitch.compare(ROBOT_FMS_LEFT) == 0) {	// Else alliance switch is LEFT
			if (scale.compare(ROBOT_FMS_RIGHT) == 0) {		// If scale is RIGHT (case LR)
				cmd = new(AutoPos1Switch);					// Attack the switch
			}
			else if (scale.compare(ROBOT_FMS_LEFT) == 0) {	// Else scale is LEFT (case LL)
				// Both are LEFT, use SmartDashboard (switch or scale)
				if (allowScale) {							// If dashboard setting says TAKE THE SCALE
					cmd = new(AutoPos1Scale);				//		prefer the scale
				}
				else {										// Else (any other value)
					cmd = new(AutoPos1Switch);				//		go for the switch
				}
			}
			else {
				std::printf("2135: Auto Pos 1 - unrecognized scale side\n");
				cmd = new(AutoPosANYMove);					// Drive to auto line
			}
		}

		if (cmd != nullptr) {
			cmd->Start();									// Start the correct command
		}
		isFinished = true;									// Let this command finish
	}
	return isFinished;
}

// Called once after isFinished returns true
void AutoPos1::End() {
	std::printf("2135: Auto Pos 1 - End\n");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoPos1::Interrupted() {
	std::printf("2135: Auto Pos 1 - Interrupted\n");
}
