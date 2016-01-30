// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<Joystick> operatorJoystick;
	std::shared_ptr<JoystickButton> retractClimb;
	std::shared_ptr<JoystickButton> extendClimb;
	std::shared_ptr<JoystickButton> expel;
	std::shared_ptr<JoystickButton> acquire;
	std::shared_ptr<JoystickButton> retractArm;
	std::shared_ptr<JoystickButton> extendArm;
	std::shared_ptr<JoystickButton> frameDown;
	std::shared_ptr<JoystickButton> frameUp;
	std::shared_ptr<JoystickButton> fire;
	std::shared_ptr<Joystick> driverJoystick;
	std::shared_ptr<JoystickButton> driverInvertDirection;
	std::shared_ptr<JoystickButton> driveGear;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
public:
	OI();

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES

	std::shared_ptr<Joystick> getDriverJoystick();
	std::shared_ptr<Joystick> getOperatorJoystick();

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES
};

#endif