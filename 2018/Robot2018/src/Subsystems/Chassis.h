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
#include "../RobotConfig.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Chassis: public frc::Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<WPI_TalonSRX> motorL1;
	std::shared_ptr<WPI_TalonSRX> motorR3;
	std::shared_ptr<frc::DifferentialDrive> diffDrive;
	std::shared_ptr<WPI_TalonSRX> motorL2;
	std::shared_ptr<WPI_TalonSRX> motorR4;
    std::shared_ptr<frc::DoubleSolenoid> shifter;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	double m_driveSpin;				// Spin turn power setting

	bool m_lowGear;					// Low Gear or High Gear

public:
	Chassis();
	void InitDefaultCommand() override;
	void Periodic() override;
	void MoveWithJoystick(std::shared_ptr<Joystick>);
	void MoveSpin(bool spinRight);

	// Shifting Gears
    void MoveShiftGears(bool lowGear);
    void MoveShiftToggle(void);


	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
};

#endif
