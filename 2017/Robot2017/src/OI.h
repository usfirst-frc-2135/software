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
	std::shared_ptr<Joystick> operatorPanelB;
	std::shared_ptr<JoystickButton> operAllCamerasOff;
	std::shared_ptr<JoystickButton> operShooterCameraOn;
	std::shared_ptr<JoystickButton> operGearCameraOn;
	std::shared_ptr<JoystickButton> operClimberLowSpeed;
	std::shared_ptr<JoystickButton> operClimberReverse;
	std::shared_ptr<JoystickButton> operClimberForward;
	std::shared_ptr<Joystick> operatorPanelA;
	std::shared_ptr<JoystickButton> operGearDoorClose;
	std::shared_ptr<JoystickButton> operGearDoorOpen;
	std::shared_ptr<JoystickButton> operLightOn;
	std::shared_ptr<JoystickButton> operShooterOn;
	std::shared_ptr<JoystickButton> operBallGateClose;
	std::shared_ptr<JoystickButton> operBallGateOpen;
	std::shared_ptr<JoystickButton> operAgitatorReverse;
	std::shared_ptr<JoystickButton> operAgitatorForward;
	std::shared_ptr<JoystickButton> operIntakeExpel;
	std::shared_ptr<JoystickButton> operIntakeAcquire;
	std::shared_ptr<Joystick> driverJoystick;
	std::shared_ptr<JoystickButton> driverGearDoorClose11;
	std::shared_ptr<JoystickButton> driverClimberForward10;
	std::shared_ptr<JoystickButton> driverClimberLowPower9;
	std::shared_ptr<JoystickButton> driverClimberLowPower8;
	std::shared_ptr<JoystickButton> driverClimberForward7;
	std::shared_ptr<JoystickButton> driverGearDoorClosed6;
	std::shared_ptr<JoystickButton> driverSpinRight;
	std::shared_ptr<JoystickButton> driverSpinLeft;
	std::shared_ptr<JoystickButton> driverAlignGear;
	std::shared_ptr<JoystickButton> driverInvertDirection;
	std::shared_ptr<JoystickButton> driverShift;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
public:
	OI();

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES

	std::shared_ptr<Joystick> getDriverJoystick();
	std::shared_ptr<Joystick> getOperatorPanelA();
	std::shared_ptr<Joystick> getOperatorPanelB();

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES
};

#endif
