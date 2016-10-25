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
	std::shared_ptr<Joystick> controlBoardB;
	std::shared_ptr<JoystickButton> pIDControl;
	std::shared_ptr<JoystickButton> brakeMode;
	std::shared_ptr<JoystickButton> shootReverse;
	std::shared_ptr<JoystickButton> shootHigh;
	std::shared_ptr<JoystickButton> fire;
	std::shared_ptr<Joystick> controlBoardA;
	std::shared_ptr<JoystickButton> frameDown;
	std::shared_ptr<JoystickButton> frameUp;
	std::shared_ptr<JoystickButton> targetLight;
	std::shared_ptr<JoystickButton> basketDown;
	std::shared_ptr<JoystickButton> indexerExpel;
	std::shared_ptr<JoystickButton> indexerAcquire;
	std::shared_ptr<JoystickButton> sweeperExpel;
	std::shared_ptr<JoystickButton> sweeperAcquire;
	std::shared_ptr<JoystickButton> retractArm;
	std::shared_ptr<JoystickButton> extendArm;
	std::shared_ptr<Joystick> driverJoystick;
	std::shared_ptr<JoystickButton> frameUpDstick;
	std::shared_ptr<JoystickButton> frameDownDstick;
	std::shared_ptr<JoystickButton> sweeperExpelDstick;
	std::shared_ptr<JoystickButton> sweeperAcquireDstick;
	std::shared_ptr<JoystickButton> retractArmDstick;
	std::shared_ptr<JoystickButton> extendArmDstick;
	std::shared_ptr<JoystickButton> spinRight;
	std::shared_ptr<JoystickButton> spinLeft;
	std::shared_ptr<JoystickButton> driveInvertDirection;
	std::shared_ptr<JoystickButton> driveShift;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
public:
	OI();

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES

	std::shared_ptr<Joystick> getDriverJoystick();
	std::shared_ptr<Joystick> getControlBoardA();
	std::shared_ptr<Joystick> getControlBoardB();

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES
};

#endif
