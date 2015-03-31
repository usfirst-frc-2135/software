// RobotBuilder Version: 1.5
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
/**
 *
 *
 * @author ExampleAuthor
 */
class Chassis: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	Timer* m_speedTimer;
	double m_orientationNormal;

	double m_driveScaleFactor;
	double m_driveDistance;
	double m_driveDistanceTimed;
	double m_drivePidSpeedMin;
	double m_drivePidSpeedMax;
	double m_driveSpinTurnSpeed;

public:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	Encoder* encoderL;
	CANTalon* motorL2;
	PIDController* leftPID;
	CANTalon* motorL3;
	Encoder* encoderR;
	CANTalon* motorR4;
	PIDController* rightPID;
	CANTalon* motorR5;
	Ultrasonic* ultrasonicDrive;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	enum SpinDirection {
		kSpinTurnLeft = 0,
		kSpinTurnRight = 1
	};

	RobotDrive* robotDrive;
	Chassis();
	void InitDefaultCommand();
	void SetDriveScaleFactor( double scaleFactor );
	double GetDriveScaleFactor( void );
	void SetDriveDistance( double inches );
	double GetDriveDistance( void );
	void SetDriveDistanceTimed( double seconds );
	double GetDriveDistanceTimed( void );
	void SetDrivePidSpeedMin( double speed );
	double GetDrivePidSpeedMin( void );
	void SetDrivePidSpeedMax( double speed);
	double GetDrivePidSpeedMax( void );
	void SetDriveSpinTurnSpeed( double speed );
	double GetDriveSpinTurnSpeed( void );

	void DriveSetNeutralMode( void );
	void DriveTrainReverse();
	void DriveWithJoystick( Joystick *joystick1 );
	void DriveWithJoystickScaled( Joystick * Joystick1 );
	void DriveUsingLeftRightMotorOutputs( double leftSpeed, double rightSpeed );
	void DriveStop( void );
	void DriveSpinTurn( int direction );
	double DriveGetLeftSpeed( void );
	double DriveGetRightSpeed( void );
	double DriveGetLeftSpeedAverage( void );
	double DriveGetRightSpeedAverage( void );

	void DriveDistanceWithPIDInit( double distance );
	void DriveDistanceWithPIDExecute( void );
	bool DriveDistanceWithPIDIsAtSetpoint( void );
	void DriveDistanceWithPIDStop( void );

};

#endif
