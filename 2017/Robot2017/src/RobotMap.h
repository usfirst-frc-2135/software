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
#include "RobotDefaults.h"

#include "ctre/Phoenix.h"

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
class RobotMap {
public:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	static std::shared_ptr<WPI_TalonSRX> chassisMotorL1;
	static std::shared_ptr<WPI_TalonSRX> chassisMotorR3;
	static std::shared_ptr<WPI_TalonSRX> chassisMotorL2;
	static std::shared_ptr<WPI_TalonSRX> chassisMotorR4;
	static std::shared_ptr<DoubleSolenoid> chassisShifter;
	static std::shared_ptr<WPI_TalonSRX> intakeMotor8;
	static std::shared_ptr<WPI_TalonSRX> intakeMotor9;
	static std::shared_ptr<WPI_TalonSRX> agitatorMotor12;
	static std::shared_ptr<WPI_TalonSRX> shooterMotor14;
	static std::shared_ptr<Servo> shooterBallGate;
	static std::shared_ptr<DigitalOutput> shooterPowerEnable;
	static std::shared_ptr<DoubleSolenoid> deliveryGearDoor;
	static std::shared_ptr<WPI_TalonSRX> climberMotor18;
	static std::shared_ptr<WPI_TalonSRX> climberMotor19;
	static std::shared_ptr<Compressor> pneumaticsCompressor;
	static std::shared_ptr<PowerDistributionPanel> powerPDP;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	// New robot drive class in 2018 wpilib
	static std::shared_ptr<frc::DifferentialDrive> chassisDrive;

	static std::shared_ptr<ADXRS450_Gyro> chassisGyro;

	static void init();
};
#endif
