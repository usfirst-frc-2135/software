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
#include "../RobotDefaults.h"
#include "../frc2135/PIDOutputDriveTurn.h"
#include "../frc2135/PIDSourceDriveVision.h"
#include "../frc2135/PIDOutputDriveVision.h"

#include "ctre/Phoenix.h"

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
	std::shared_ptr<WPI_TalonSRX> motorL1;
	std::shared_ptr<WPI_TalonSRX> motorR3;
	std::shared_ptr<WPI_TalonSRX> motorL2;
	std::shared_ptr<WPI_TalonSRX> motorR4;
	std::shared_ptr<DoubleSolenoid> shifter;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<frc::DifferentialDrive> drive;

// 	const double				WheelDiaInches = 4.138;		// Crush wheel diameter
//	10/22 Test: L-encoder: -10620.0; R-encoder: 10602.0 for 290 inches distance
	const double				WheelDiaInches = 4.1722; 	// Crush wheel dia for left wheel; right = 4.1793
	const unsigned short int	USDigitalS4_CPR = 360;
	const unsigned short int	Encoder_CPR = (USDigitalS4_CPR * 4);	// Talons report CPR * 4 (each encoder signal edge)
	const double				InchesPerCount = WheelDiaInches * M_PI / (double)Encoder_CPR;
	const int					pidIndex = 0;				// PID slot index for sensors
	const int					timeout = 100;				// CAN timeout in msec to wait for response

	std::shared_ptr<ADXRS450_Gyro> gyro;

	double m_driveDirection;		// Allows chassis drive direction change
	double m_driveScaling;			// Scaling applied to joystick for SW shifting
	double m_turnScaling;			// Turn scaling (1.0 is disabled, < 1.0 is max X output)
	double m_driveSpin;				// Spin turn power setting
	bool m_brakeMode; 				// Brake or Coast mode for talons
	bool m_invertEnable;			// Disables or enables invert drive direction

	double m_turnKP;				// Proportional value for PID for DriveTurn function

	double m_pidTargetCounts; 	// Number of rotations to drive in Drive Distance
	int m_CL_allowError;			// Closed loop allowable error
	bool m_CL_pidStarted;			// Flag to indicate PID has started and CL error is valid
	double m_pidAngle;				// Number of degrees to turn in Drive Turn

	bool m_lowGear;					// Low Gear or High Gear
	Timer m_safetyTimer;			// Safety timer for use during autonomous modes
	double m_safetyTimeout;			// Time in seconds for safety timer

	PIDOutputDriveTurn *driveTurnPIDOutput;	// Drive Turn to angle using gyro - initialize output
	PIDController *driveTurnPIDLoop;		// Drive Turn PID controller loop

	PIDOutputDriveVision *driveVisionPIDOutput;	// Drive with Vision to angle using gyro - initialize output
	PIDSourceDriveVision *driveVisionPIDSource;	// Drive with Vision PID source loop
	PIDController *driveVisionPIDLoop;		// Drive with Vision PID controller loop

public:
	Chassis();
	void InitDefaultCommand();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

	// Put added public methods here in same order as in file

	void Initialize(frc::Preferences *prefs);
	void UpdateSmartDashboardValues(void);
	void MoveWithJoystick(std::shared_ptr<Joystick>);
	void MoveSpin(bool spinLeft);
	void MoveInvertDriveDirection(void);
	void MoveScaleMaxSpeed(bool scaled);
	void MoveSetBrakeNotCoastMode(bool brakeMode);
	void MoveUsingMotorOutputs(double motorInputLeft, double motorInputRight);

	// Sequence for Drive Distance
	void MoveDriveDistancePIDInit(double inches);
	void MoveDriveDistancePIDExecute(void);
	bool MoveDriveDistanceIsPIDAtSetpoint(void);
	void MoveDriveDistancePIDStop(void);

	// Sequence for Drive to Turn to a Heading
	void MoveDriveHeadingInit(double angle);
	bool MoveDriveHeadingIsPIDAtSetPoint(void);
	void MoveDriveHeadingStop(void);

	// Sequence for Drive to Turn to a Heading with Vision
	void MoveDriveVisionHeadingDistanceInit(double angle, double distance);
	bool MoveDriveVisionHeadingIsPIDAtSetPoint(void);
	void MoveDriveVisionHeadingStop(void);

	void MoveShiftGears(bool lowGear);
	void MoveShiftToggle(void);

	int GetEncoderPosition(std::shared_ptr<WPI_TalonSRX> mtr);
};

#endif
