// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#ifndef ROBOTMAP_H
#define ROBOTMAP_H
#include "WPILib.h"
/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
class RobotMap {
public:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	static Ultrasonic* chassisUltrasonicDrive;
	static Relay* chassisLEDRelay;
	static SpeedController* chassisLeftDriveMotor;
	static Encoder* chassisLeftDriveEncoder;
	static PIDController* chassisLeftDrivePID;
	static SpeedController* chassisRightDriveMotor;
	static Encoder* chassisRightDriveEncoder;
	static PIDController* chassisRightDrivePID;
	static DoubleSolenoid* transmissionShifterSolenoid;
	static DoubleSolenoid* sweeperArmExtendSolenoid;
	static SpeedController* sweeperMotorWheels;
	static DoubleSolenoid* shooterTriggerSolenoid;
	static SpeedController* shooterRetractMotor;
	static DigitalInput* shooterRetractLimit1;
	static DigitalInput* shooterRetractLimit2;
	static Encoder* shooterRetractEncoder;
	static DoubleSolenoid* ballGateCloseSolenoid;
	static DigitalInput* ballGateBallDetectLimit;
	static Compressor* pneumaticsCompressor;
	static AnalogChannel* pneumaticsAnalogInput1;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	static void init();
	static DriverStation* driverStation;
	static RobotDrive* driveTrain;
};
#endif
