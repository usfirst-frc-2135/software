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

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "ctre/Phoenix.h"
#include "frc/Solenoid.h"

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

/**
 *
 *
 * @author ExampleAuthor
 */
class Shooter: public frc::Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
std::shared_ptr<WPI_TalonSRX> motorSH10;
std::shared_ptr<WPI_TalonSRX> motorSH11;
std::shared_ptr<frc::Solenoid> shooterIndexer;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	// Declare constants
	int				m_shooterDebug = 0;				// DEBUG flag to disable/enable extra logging calls
	const int		m_slotIndex = 0;				// Motor controller profile slot index
	const int 		m_pidIndex = 0;					// PID slot index for sensors
	const int		m_timeout = 20;					// CAN timeout in msec to wait for response
	const double	COUNTS_PER_ROTATION = (1024*4);	// CPR is 1024 and multipled by 4 because it is a quadrature encoder

	// Declare module variables
	bool		m_talonValidSH10;			// Health indicator for shooter talon 10
	bool		m_talonValidSH11;			// Health indicator for shooter talon 11

	int 		m_shooterLevel;				// Current shooter speed level
	double		m_targetVelocityRPM;		// Target shooter velocity in RPM
	double		m_targetVelocityNative;		// Target shooter velcoity in native units per 100 ms
	double		m_curVelocityRPM;			// Current shooter velocity in RPM

	frc::Timer	m_safetyTimer;				// Safety timer for use in shooter
	double		m_safetyTimeout;			// Seconds that the timer ran before stopping

	// Configuration file parameters
	double		m_onSpeed;
	double		m_reverseSpeed;
	double		m_fwdOutput;
	double		m_revOutput;

	double		m_pidKf;					// Shooter PID force constant
	double		m_pidKp;					// Shooter PID proportional constant
	double		m_pidKi;					// Shooter PID integral constant
	double		m_pidKd;					// Shooter PID derivative constant
	double		m_neutralDeadband;			// Shooter PID neutral deadband in percent

	double m_smartDashOutput;
	double m_smartDashSpeed;

public:
Shooter();
	void InitDefaultCommand() override;
	void Periodic() override;
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

	// Shooter motor control states

	enum {
		STOP_SPEED = 0,				// Stop shooter
		ON_SPEED = 1,				// Shooter velocity
		REVERSE_SPEED = -1,			// Shooter reverse		
		SMARTDASH_SPEED = 2
	};

	void Initialize(void);
	void FaultDump(void);

	// Conversion functions between RPM and CTRE Native Units / 100ms
	double RpmToNative(double rpm);
	double NativeToRpm(double native);

	void SetShooterMotorOutput(int direction);

	void SetShooterSpeedInit(int level);
};

