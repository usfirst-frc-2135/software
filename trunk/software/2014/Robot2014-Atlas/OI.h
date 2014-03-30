// RobotBuilder Version: 1.0
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
	Joystick* operatorJoystick;
	JoystickButton* operatorShooterFire;
	JoystickButton* operatorShooterReload;
	JoystickButton* operatorBallGateClose;
	JoystickButton* operatorBallGateOpen;
	JoystickButton* operatorSweeperRetract;
	JoystickButton* operatorSweeperDeploy;
	JoystickButton* operatorSweeperReject;
	JoystickButton* operatorSweeperAquire;
	Joystick* driverJoystick;
	JoystickButton* driverBallGateClose;
	JoystickButton* driverBallGateOpen;
	JoystickButton* driverSweeperRetract;
	JoystickButton* driverSweeperDeploy;
	JoystickButton* driverSweeperReject;
	JoystickButton* driverSweeperAcquire;
	JoystickButton* driverDriveSpinLeft;
	JoystickButton* driverDriveSpinRight;
	JoystickButton* driverDrivetrainInvert;
	JoystickButton* shifter;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
public:
	OI();
 
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES
	Joystick* getDriverJoystick();
	Joystick* getOperatorJoystick();
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES
};
#endif
