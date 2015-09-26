// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#ifndef CHASSIS_H
#define CHASSIS_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
/**
 *
 *
 * @author ExampleAuthor
 */
class Chassis: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	double m_orientationNormal;
	Timer* m_speedTimer;
	double m_minRange;
	double m_maxRange;
public:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	Ultrasonic* ultrasonicDrive;
	Relay* lEDRelay;
	SpeedController* leftDriveMotor;
	Encoder* leftDriveEncoder;
	PIDController* leftDrivePID;
	SpeedController* rightDriveMotor;
	Encoder* rightDriveEncoder;
	PIDController* rightDrivePID;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	RobotDrive* drvTrain;
	Chassis();
	void InitDefaultCommand();
	void DriveWithJoystick( Joystick* driverJoystick );
	void DriveUsingLeftRightMotorOutputs( double left, double right );
	void ReverseDriveTrain( void );
	void DriveDistanceWithPIDInit( double distance );
	void DriveDistanceWithPIDExecute( void );
	bool DriveDistanceWithPIDIsAtSetpoint( void );
	void DriveDistanceWithPIDStop( void );
	double GetLeftSpeed( void );
	double GetRightSpeed( void );
	double GetDistanceUltrasonic( void );
	void UpdateDistance( void );
	double GetLeftSpeedAverage( void );
	double GetRightSpeedAverage( void );
	void UpdateAccelerometer( void );
	
};
#endif
