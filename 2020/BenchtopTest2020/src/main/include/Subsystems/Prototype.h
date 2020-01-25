// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include <iostream>
#include <memory>
#include <string>

#include "frc/commands/Subsystem.h"
#include "frc/WPILib.h"
#include "ctre/Phoenix.h"
#include "ctre/phoenix/sensors/PigeonIMU.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Prototype: public frc::Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
std::shared_ptr<WPI_TalonSRX> talonSRX1;
std::shared_ptr<WPI_TalonSRX> talonSRX2;
std::shared_ptr<frc::DigitalInput> limitSwitch1;
std::shared_ptr<frc::DigitalInput> limitSwitch2;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	std::shared_ptr<PigeonIMU> pigeonIMU1;

	bool m_talonInvert1 = false;
	bool m_talonInvert2 = false;

	frc::AnalogInput *reflSensor;

public:
	Prototype();
	void InitDefaultCommand() override;
	void Periodic() override;
	void MoveWithJoystick(std::shared_ptr<frc::Joystick> jstick);
	void InvertMotor1(); 
	void InvertMotor2();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
	void ReadSensorVelocity();
};

#endif
