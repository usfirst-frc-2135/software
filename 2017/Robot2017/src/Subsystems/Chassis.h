// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef CHASSIS_H
#define CHASSIS_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "CANTalon.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Chassis: public Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<CANTalon> motorL2;
	std::shared_ptr<CANTalon> motorL3;
	std::shared_ptr<CANTalon> motorR4;
	std::shared_ptr<CANTalon> motorR5;
	std::shared_ptr<AnalogGyro> analogGyro1;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	double m_driveDirection;		// Allows chassis drive direction change
	bool m_scaled;					// Indicates scaling is applied
	double m_driveScalingFactor;	// Scaling applied to joystick for SW shifting
	double m_driveSpinSetting;		//Spin turn power setting

public:
	RobotDrive* robotDrive;
	Chassis();
	void InitDefaultCommand();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
	void MoveWithJoystick(std::shared_ptr<Joystick>);
	void SetVoltRampRate(double voltageRampRate);
	void MoveLowShift(bool scaled);
	void MoveSpin(bool spinLeft);
	void MoveStop(void);
	void ReverseDriveTrain(void);
	double ReadGyro(void);
	void ResetGyro(void);
};

#endif
