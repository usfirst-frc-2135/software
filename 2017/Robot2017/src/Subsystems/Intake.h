// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#ifndef INTAKE_H
#define INTAKE_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

#include "ctre/phoenix/MotorControl/CAN/TalonSRX.h"
using namespace CTRE::MotorControl;

/**
 *
 *
 * @author ExampleAuthor
 */
class Intake: public Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<CAN::TalonSRX> motor8;
	std::shared_ptr<CAN::TalonSRX> motor9;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	const double intakeSpeed = -1.0;		// Default motor speed

public:
	Intake();
	void InitDefaultCommand();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

	enum { INTAKE_STOP = 0, INTAKE_FORWARD = 1, INTAKE_REVERSE = -1};

	// Put added public methods here in same order as in file
	void Initialize(frc::Preferences *prefs);
	void UpdateSmartDashboardValues(void);
	void ArmExtend(bool extend);
	void SetMotorSpeed(int enabled);
};

#endif
