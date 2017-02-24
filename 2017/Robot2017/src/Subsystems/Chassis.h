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

#define M_WHEEL_DIA 4	// number of inches in diameter of drive wheels
// TODO: DONE - This should be 360 CPR
#define M_COUNTS_PER_ROTATION 360	// number of counts per rotation

// These classes should probably be added below the Chassis class to be more Robotbuilder friendly
class TurnOutput: public PIDOutput {
	public:
	std::shared_ptr<RobotDrive> myRobotDrive;
	TurnOutput (std::shared_ptr<RobotDrive> robotDrive){
		myRobotDrive = robotDrive;
	}
	void PIDWrite(double output) {
//		printf("==>Passing to Arcade Drive output = %3f\n", output);
		myRobotDrive->ArcadeDrive (0.0, output, true);
		SmartDashboard::PutNumber("TurnOutput", output);
	}
};

class GyroAngleSource: public PIDSource {
	public:
	frc::ADXRS450_Gyro *myGyro;
	GyroAngleSource (frc::ADXRS450_Gyro *gyro){
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

	const unsigned short int	USDigitalS4_360 = 360;

	std::shared_ptr<ADXRS450_Gyro> gyro;

	double m_driveDirection;		// Allows chassis drive direction change
	bool m_scaled;					// Indicates scaling is applied
	double m_driveScalingFactor;	// Scaling applied to joystick for SW shifting
	double m_driveSpinSetting;		// Spin turn power setting
	bool m_brakeMode; 				// Brake or Coast mode for talons
	double m_absTolerance;			// PID absolute tolerance
	double m_rotations; 			// Number of rotations to drive in Drive Distance
	bool m_lowGear;					// Low Gear or High Gear
	double m_safetyInches;			// Distance used in safety timer
	Timer m_safetyTimer;
	TurnOutput *turnOutput;
	GyroAngleSource *gyroAngle;
	PIDController *turnControl;


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
	void MoveSetVoltageRamp(double voltageRampRate);
	void MoveToggleBrakeMode(void);
	void MoveUsingMotorOutputs(double motorInputLeft, double motorInputRight);

	// Sequence for Drive Distance
	void MoveDriveDistancePIDInit(double inches);
	void MoveDriveDistancePIDExecute(void);
	bool MoveDriveDistancePIDAtSetpoint(void);
	void MoveDriveDistancePIDStop(void);

	void MoveDriveHeadingDistance(double inches, double angle);
	bool MoveDriveHeadingAtSetPoint(void);
	void MoveDriveHeadingStop(void);
	void MoveShiftGears(bool lowGear);

	void ResetEncoder(void);
	std::pair<double, double> ReadEncoder(void);
	void ResetGyro(void);
	double ReadGyro(void);
};

#endif
