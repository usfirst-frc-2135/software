// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "Firing.h"
#include "../Robotmap.h"
#include "../Commands/FireReload.h"
Firing::Firing() : Subsystem("Firing") {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	firingPin = RobotMap::firingFiringPin;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
}
    
void Firing::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
	SetDefaultCommand(new FireReload());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
//
// Enable the firing pin pneumatic
void Firing::EnableFiringPin(){
	RobotMap::driverStationLCD->PrintfLine( DriverStationLCD::kUser_Line6, "Fire:   %s", "Enable" );
	firingPin->Set(DoubleSolenoid::kReverse);
}
//
// Disable the firing pin pneumatic
void Firing::DisableFiringPin(){
	RobotMap::driverStationLCD->PrintfLine( DriverStationLCD::kUser_Line6, "Fire:   %s", "Disable" );
	firingPin->Set(DoubleSolenoid::kForward);
}
