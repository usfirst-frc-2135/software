// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include "Delivery.h"
#include "../RobotMap.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Delivery::Delivery() : Subsystem("Delivery") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    gearHolder = RobotMap::deliveryGearHolder;
    gearDoor = RobotMap::deliveryGearDoor;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    printf("2135: Delivery Constructor\n");
}

void Delivery::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void Delivery::Initialize(frc::Preferences *prefs)
{
	// TODO: Initialize SmartDashboard values - if any
	printf("2135: Delivery Initialize\n");
}

void Delivery::UpdateSmartDashboardValues(void)
{

}

void Delivery::GearRelease(bool open)
{
	if (open) {
		gearHolder->Set(gearHolder->kForward);
	}
	else {
		gearHolder->Set(gearHolder->kReverse);
	}
}

void Delivery::DoorClose(bool open)
{
	if (open) {
		gearDoor->Set(gearDoor->kForward);
	}
	else {
		gearDoor->Set(gearDoor->kReverse);
	}
}
