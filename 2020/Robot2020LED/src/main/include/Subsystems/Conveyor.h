// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc2135/RobotConfig.h>
#include <frc2135/TalonUtils.h>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "ctre/Phoenix.h"
#include "frc/DigitalInput.h"

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

/**
 *
 *
 * @author ExampleAuthor
 */
class Conveyor: public frc::Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
std::shared_ptr<WPI_TalonSRX> motorCV8;
std::shared_ptr<frc::DigitalInput> cVPhotosensor;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	// Declare constants
	int			m_conveyorDebug = 0;		// DEBUG flag to disable/enable extra logging calls		
	const int	m_timeout = 20;				// CAN timeout in msec to wait for response

	// Declare module variables

	double 		m_acquireSpeed;
	double 		m_holdSpeed;
	double 		m_expelSpeed;

	bool		m_talonValidCV8;			// Health indicator for conveyor talon

	bool		m_detectPowerCellOn;

public:
Conveyor();
	void InitDefaultCommand() override;
	void Periodic() override;
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

	//Conveyor motor control states
		enum {
		CONVEYOR_STOP = 0,
		CONVEYOR_UP = 1,
		CONVEYOR_DOWN = -1,
		CONVEYOR_HOLD = 3
	};

	void Initialize(void);
	void SetConveyorMotorSpeed(int direction);
	void FaultDump(void);


};

