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
	
	
	
	
	
	
	
	
	
	
	std::shared_ptr<frc::Joystick> dStick;
	std::shared_ptr<frc::JoystickButton> elevatorDown;
	std::shared_ptr<frc::JoystickButton> elevatorUp;
	std::shared_ptr<frc::JoystickButton> cubeExpel;
	std::shared_ptr<frc::JoystickButton> cubeAcquire;
	std::shared_ptr<frc::JoystickButton> shiftSpeed;
	std::shared_ptr<frc::JoystickButton> spinLeft;
	std::shared_ptr<frc::JoystickButton> spinRight;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
public:
	OI();

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES

	std::shared_ptr<frc::Joystick> getDStick();

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES
};

#endif
