// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef GRIPPER_H
#define GRIPPER_H
#include "frc/WPILib.h"
#include "ctre/Phoenix.h"

#include "RobotDefaults.h"
#include "RobotMap.h"
#include "frc2135/TalonSRXUtils.h"
#include "frc2135/RobotConfig.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Gripper: public frc::Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<WPI_TalonSRX> motorL11;
	std::shared_ptr<WPI_TalonSRX> motorR12;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	//	Declare constants
	const bool	m_gripperDebug = false;			// Debug flag to disable extra logging calls
	const int	m_timeout = 10;					// CAN timeout in msec to wait for response

	double 		m_acquireSpeed;
	double 		m_holdSpeed;
	double 		m_expelSpeed;
	bool		m_spinLeft;

public:
	Gripper();
	void InitDefaultCommand() override;
	void Periodic() override;

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

	// Gripper motor control states
	enum {
		GRIPPER_STOP = 0,
		GRIPPER_FORWARD = 1,
		GRIPPER_REVERSE = -1,
		GRIPPER_SPIN = 2,
		GRIPPER_HOLD = 3
	};

	bool			m_talonValidL11;				// Health indicator for gripper Talon Left 11
	bool			m_talonValidR12;				// Health indicator for gripper Talon Right 12

	void Initialize(void);
	void SetGripperMotorSpeed(int speed);
};

#endif