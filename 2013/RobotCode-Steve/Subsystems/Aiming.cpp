// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "Aiming.h"
#include "../Robotmap.h"
#include "../Commands/AimUp.h"
Aiming::Aiming() : Subsystem("Aiming") {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	elevation = RobotMap::aimingElevation;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
}
    
void Aiming::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
	SetDefaultCommand(new AimUp());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
//
// Enable the firing pin pneumatic
void Aiming::AimingElevationUp(){
//	RobotMap::driverStationLCD->Printf( DriverStationLCD::kUser_Line2, 10, "Aim UP" );
	elevation->Set( elevation->kForward );
}
//
// Disable the firing pin pneumatic
void Aiming::AimingElevationDown(){
//	RobotMap::driverStationLCD->Printf( DriverStationLCD::kUser_Line2, 10, "Aim DN" );
	elevation->Set( elevation->kReverse );
}
