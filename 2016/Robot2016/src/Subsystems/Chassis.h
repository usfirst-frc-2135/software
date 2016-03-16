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

#define M_WHEEL_DIA	8	// number of inches in diameter of drive wheels
#define M_COUNTS_PER_ROTATION 360	// number of counts per rotation

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
	std::shared_ptr<Encoder> leftEncoder;
	std::shared_ptr<PIDController> leftPID;
	std::shared_ptr<CANTalon> motorR4;
	std::shared_ptr<Encoder> rightEncoder;
	std::shared_ptr<PIDController> rightPID;
	std::shared_ptr<CANTalon> motorL3;
	std::shared_ptr<CANTalon> motorR5;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	double m_drivePidSpeedMin;		// UNUSED?
	double m_drivePidSpeedMax;		// UNUSED?
	double m_driveDistance;			// UNUSED?
	double m_driveDistanceTimed;	// UNUSED?
	double m_driveDirection;		// Allows chassis drive direction change
	double m_rotations;				// Number of rotations for drive distance
	double m_speedControl;			// Scaling applied to joystick for SW shifting
	bool m_scaled;					// Indicates scaling is applied

public:
	RobotDrive* robotDrive;
	Chassis();
	void InitDefaultCommand();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
	void Initialize(Preferences *prefs);
	void MoveWithJoystick(std::shared_ptr<Joystick>);
	void MoveUsingLeftRightMotorOutputs(double, double);
	void MoveStop(void);
	void MoveLowShift(bool scaled);
	void ReverseDriveTrain(void);

	void MoveDistanceWithPIDInit(double distance);
	void MoveDistanceWithPIDExecute(void);
	bool MoveDistanceWithPIDIsAtSetpoint(void);
	void MoveDistanceWithPIDStop(void);
};

#endif
