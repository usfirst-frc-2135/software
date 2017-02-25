// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef ROBOTMAP_H
#define ROBOTMAP_H
#include "WPILib.h"
#include "CANTalon.h"


/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
class RobotMap {
public:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	static std::shared_ptr<CANTalon> chassisMotorL1;
	static std::shared_ptr<CANTalon> chassisMotorR3;
	static std::shared_ptr<RobotDrive> chassisRobotDrive;
	static std::shared_ptr<CANTalon> chassisMotorL2;
	static std::shared_ptr<CANTalon> chassisMotorR4;
	static std::shared_ptr<DoubleSolenoid> chassisShifter;
	static std::shared_ptr<CANTalon> intakeMotor8;
	static std::shared_ptr<CANTalon> intakeMotor9;
	static std::shared_ptr<DoubleSolenoid> intakeArmDeploy;
	static std::shared_ptr<CANTalon> agitatorMotor12;
	static std::shared_ptr<CANTalon> shooterMotor14;
	static std::shared_ptr<Servo> shooterBallGate;
	static std::shared_ptr<DoubleSolenoid> deliveryGearHolder;
	static std::shared_ptr<DoubleSolenoid> deliveryGearDoor;
	static std::shared_ptr<CANTalon> climberMotor18;
	static std::shared_ptr<CANTalon> climberMotor19;
	static std::shared_ptr<Compressor> pneumaticsCompressor;
	static std::shared_ptr<PowerDistributionPanel> powerPDP;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

//#define USE_ADXRS450_GYRO
#if USE_ADXRS450_GYRO
	static std::shared_ptr<ADXRS450_Gyro> chassisGyro;
#else
	static std::shared_ptr<AnalogGyro> chassisGyro;
#endif

	static void init();
};
#endif
