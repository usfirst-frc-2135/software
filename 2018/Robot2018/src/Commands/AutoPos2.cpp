// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include <Commands/AutoPos2SwitchLeft.h>
#include <Commands/AutoPos2SwitchRight.h>
#include "AutoPos2.h"
#include "AutoPosANYMove.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

AutoPos2::AutoPos2(): frc::Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void AutoPos2::Initialize() {
	std::printf("2135: Auto Pos 2 - Init\n");

}

// Called repeatedly when this Command is scheduled to run
void AutoPos2::Execute() {
	// Wait for gameData before scheduling next steps
}

// Make this return true when this Command no longer needs to run execute()
bool AutoPos2::IsFinished() {
	bool			isFinished = false;
	std::string 	alliSwitch;			// Holds alliance switch game data setting
	std::string 	scale;				// Holds scale game data setting
	frc::Command	* cmd = nullptr;	// Pointer to command/command group to run

	// Check if gameData has been sent
	alliSwitch = SmartDashboard::GetString(ROBOT_FMSALLISWITCH, ROBOT_FMS_UNINIT);
	// If not the uninitialized string, then new data received
	if (alliSwitch.compare(ROBOT_FMS_UNINIT) != 0) {
		// Select group command for Pos 2 decisions here
		scale = SmartDashboard::GetString(ROBOT_FMSSCALE, ROBOT_FMS_UNINIT);
    	std::printf("2135: Auto Pos 2 - AlliSwitch: %s Scale: %s\n", alliSwitch.c_str(), scale.c_str());

   		if (alliSwitch.compare(ROBOT_FMS_RIGHT) == 0) {		 // If alliance switch is RIGHT
    		cmd = new(AutoPos2SwitchRight);					 // Attack the switch plate on the right
    	}
		else if (alliSwitch.compare(ROBOT_FMS_LEFT) == 0) {	 // Else alliance switch is LEFT
    		cmd = new(AutoPos2SwitchLeft);				     // Attack the switch plate on the left
    	}

		if (cmd != nullptr) {
			cmd->Start();									// Start the correct command
		}
		isFinished = true;									// Let this command finish
	}
	return isFinished;
}

// Called once after isFinished returns true
void AutoPos2::End() {
	std::printf("2135: Auto Pos 2 - End\n");

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoPos2::Interrupted() {
	std::printf("2135: Auto Pos 2 - Interrupted\n");
}
