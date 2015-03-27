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
	double m_orientationNormal;
	double m_scaleFactor;
	Timer* m_speedTimer;
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
	RobotDrive* robotDrive;
	Chassis();
	void InitDefaultCommand();
	void DriveSetNeutralMode( void );
	void DriveDistanceWithPIDInit( double distance );
	void DriveDistanceWithPIDExecute ();
	bool DriveDistanceWithPIDIsAtSetpoint ();
	void DriveDistanceWithPIDStop ();
	void DriveWithJoystick(Joystick *joystick1);
	void DriveWithJoystickScaled( Joystick * Joystick1 );
	void DriveUsingLeftRightMotorOutputs(double left, double right);
	void DriveTrainReverse();
	double DriveGetLeftSpeed( void );
	double DriveGetRightSpeed( void );
	double DriveGetLeftSpeedAverage( void );
	double DriveGetRightSpeedAverage( void );
};

#endif
