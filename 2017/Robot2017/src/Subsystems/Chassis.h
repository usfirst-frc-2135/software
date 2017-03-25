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
#include "../RobotDefaults.h"

///////////////////////////////////////////////////////////////////////////////////////////////////

//	Turn PID controller class definitions

class TurnOutput: public PIDOutput {
public:
	std::shared_ptr<RobotDrive> myRobotDrive;

	TurnOutput (std::shared_ptr<RobotDrive> robotDrive) {
		myRobotDrive = robotDrive;
	}

	void PIDWrite(double output) {
		myRobotDrive->ArcadeDrive (0.0, output, false);
		// TODO: Remove this after tuning
		SmartDashboard::PutNumber(CHS_TURNPID_OUT_L, output);
		SmartDashboard::PutNumber(CHS_TURNPID_OUT_R, -output);
	}
};

class GyroAngleSource: public PIDSource {
public:
	frc::ADXRS450_Gyro *myGyro;

	GyroAngleSource (frc::ADXRS450_Gyro *gyro) {
		myGyro = gyro;
	}

	double PIDGet() {
		return myGyro->GetAngle();
	}
};

//	Camera Vision Drive PID controller class definitions

class CameraVisionDriveOutput: public PIDOutput {
public:
	std::shared_ptr<RobotDrive> myRobotDrive;
	std::shared_ptr<Joystick> myJoystick;

	CameraVisionDriveOutput (std::shared_ptr<RobotDrive> robotDrive, std::shared_ptr<Joystick> joystick) {
		myRobotDrive = robotDrive;
		myJoystick = joystick;
	}

	void PIDWrite(double output) {
		double visionAngle = SmartDashboard::GetNumber(CAM_TURNANGLE, CAM_TURNANGLE_D);
		double currentAngle = SmartDashboard::GetNumber(CHS_GYROANGLE, 0.0);
		output = (currentAngle + visionAngle) * CAM_TURNKP_D;
		myRobotDrive->ArcadeDrive (myJoystick->GetY(), output, false);
		// TODO: Remove this after tuning
		SmartDashboard::PutNumber(CHS_TURNPID_OUT_L, output);
		SmartDashboard::PutNumber(CHS_TURNPID_OUT_R, -output);
	}
};

class CameraAngleSource: public PIDSource {
public:
	frc::ADXRS450_Gyro *myGyro;

	CameraAngleSource (frc::ADXRS450_Gyro *gyro) {
		myGyro = gyro;
	}

	double PIDGet() {
		return myGyro->GetAngle();
	}
};

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
	std::shared_ptr<CANTalon> motorL1;
	std::shared_ptr<CANTalon> motorR3;
	std::shared_ptr<RobotDrive> robotDrive;
	std::shared_ptr<CANTalon> motorL2;
	std::shared_ptr<CANTalon> motorR4;
	std::shared_ptr<DoubleSolenoid> shifter;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	const unsigned short int	USDigitalS4_CPR_120 = 120;
//	const double				WheelDiaInches = 4.138;		// Crush wheel diameter
	const double				WheelDiaInches = 4.1699;	// Brush wheel diameter

#ifdef USE_ADXRS450_GYRO
	std::shared_ptr<ADXRS450_Gyro> gyro;
#else
	std::shared_ptr<AnalogGyro> gyro;
#endif

	double m_driveDirection;		// Allows chassis drive direction change
	double m_driveScaling;			// Scaling applied to joystick for SW shifting
	double m_driveSpin;				// Spin turn power setting
	bool m_brakeMode; 				// Brake or Coast mode for talons

	double m_pidTargetRotations; 	// Number of rotations to drive in Drive Distance
	int m_CL_allowError;			// Closed loop allowable error
	bool m_CL_pidStarted;			// Flag to indicate PID has started and CL error is valid
	double m_pidAngle;				// Number of degrees to turn in Drive Turn

	bool m_lowGear;					// Low Gear or High Gear
	Timer m_safetyTimer;			// Safety timer for use during autonomous modes

	TurnOutput *turnOutput;
	PIDController *turnControl;
	CameraVisionDriveOutput *cameraVisionDriveOutput;
	PIDController *cameraVisionDriveControl;


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
	void MoveDriveHeadingDistanceInit(double angle);
	bool MoveDriveHeadingIsPIDAtSetPoint(void);
	void MoveDriveHeadingStop(void);

	// Sequence for Drive to Turn to a Heading with Vision
	void MoveDriveVisionHeadingDistanceInit(double angle);
	bool MoveDriveVisionHeadingIsPIDAtSetPoint(void);
	void MoveDriveVisionHeadingStop(void);
	double MoveDriveVisionAngle(void);

	void MoveShiftGears(bool lowGear);
};

#endif
