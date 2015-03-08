// RobotBuilder Version: 1.5
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
	Joystick* joystick3;
	JoystickButton* operatorElevatorDown;
	JoystickButton* operatorElevatorUp;
	JoystickButton* operatorStackerRelease;
	JoystickButton* operatorStackerHold;
	JoystickButton* operatorStackerExpel;
	JoystickButton* operatorStackerAcquire;
	JoystickButton* operatorIntakeRelease;
	JoystickButton* operatorIntakeHold;
	JoystickButton* operatorIntakeExpelR;
	JoystickButton* operatorIntakeExpelL;
	JoystickButton* operatorIntakeAcquireR;
	JoystickButton* operatorIntakeAcquireL;
	Joystick* joystick2;
	JoystickButton* driverHWheelEnable;
	JoystickButton* driverHWheelDeploy;
	Joystick* joystick1;
	JoystickButton* driverDisableElevatorPID;
	JoystickButton* driverEnableElevatorPID;
	JoystickButton* driverTurn;
	JoystickButton* driverSpinRight;
	JoystickButton* driverSpinLeft;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
public:
	OI();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES

	Joystick* getJoystick1();
	Joystick* getJoystick2();
	Joystick* getJoystick3();

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES
};

#endif
