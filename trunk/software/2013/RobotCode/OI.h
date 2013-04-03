// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#ifndef OI_H
#define OI_H
#include "WPILib.h"
class OI {
private:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	Joystick* operatorStick;
	JoystickButton* operatorButton12;
	JoystickButton* operatorButton11;
	JoystickButton* operatorButton10;
	JoystickButton* operatorButton9;
	JoystickButton* operatorButton8;
	JoystickButton* operatorButton7;
	JoystickButton* operatorButton6;
	JoystickButton* operatorButton5;
	JoystickButton* operatorButton4;
	JoystickButton* operatorButton3;
	JoystickButton* operatorButton2;
	JoystickButton* operatorTrigger;
	Joystick* driverStick;
	JoystickButton* driverButton12;
	JoystickButton* driverButton11;
	JoystickButton* driverButton10;
	JoystickButton* driverButton9;
	JoystickButton* driverButton8;
	JoystickButton* driverButton7;
	JoystickButton* driverButton6;
	JoystickButton* driverButton5;
	JoystickButton* driverButton4;
	JoystickButton* driverButton3;
	JoystickButton* driverButton2;
	JoystickButton* driverTrigger;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
public:
	OI();
 
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES
	Joystick* getDriverStick();
	Joystick* getOperatorStick();
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES
	
	double OI::getOperatorThrottle();
	double OI::getDriverThrottle();
};
#endif
