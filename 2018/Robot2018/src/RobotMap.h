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


#include "RobotDefaults.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "WPILib.h"
#include "ctre/Phoenix.h"

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
class RobotMap {
public:
#ifndef ROBORIO_STANDALONE
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	static std::shared_ptr<WPI_TalonSRX> drivetrainMotorL1;
	static std::shared_ptr<WPI_TalonSRX> drivetrainMotorR3;
	static std::shared_ptr<frc::DifferentialDrive> drivetrainDiffDrive;
	static std::shared_ptr<WPI_TalonSRX> drivetrainMotorL2;
	static std::shared_ptr<WPI_TalonSRX> drivetrainMotorR4;
	static std::shared_ptr<frc::DoubleSolenoid> drivetrainShifter;
	static std::shared_ptr<WPI_TalonSRX> elevatorMotorL7;
	static std::shared_ptr<WPI_TalonSRX> elevatorMotorR8;
	static std::shared_ptr<frc::DigitalInput> elevatorHallLimit;
	static std::shared_ptr<WPI_TalonSRX> gripperMotorL11;
	static std::shared_ptr<WPI_TalonSRX> gripperMotorR12;
	static std::shared_ptr<WPI_TalonSRX> gripperMotorW14;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
#endif

#ifdef ROBOTBENCHTOPTEST
	static std::shared_ptr<WPI_TalonSRX> elevatorMotorL7;
	static std::shared_ptr<frc::DigitalInput> elevatorHallLimit;
	static std::shared_ptr<WPI_TalonSRX> elevatorMotorR8;
#endif

	static void init();
};
#endif
