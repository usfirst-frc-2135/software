// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef WRIST_H
#define WRIST_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../RobotDefaults.h"
#include "../frc2135/RobotConfig.h"

#define	TALON_W14_PRESENT

/**
 *
 *
 * @author ExampleAuthor
 */
class Wrist: public frc::Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
#ifndef ROBORIO_STANDALONE
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<WPI_TalonSRX> motorW14;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
#endif
	double m_wristSpeed;

	const int 		m_slotIndex = 0;				// Motor controller profile slot index
	const int 		m_pidIndex = 0; 				// PID Slot index for sensors
	const int 		m_timeout = 10;					// CAN timeout in msec to wait for response
	const double COUNTS_PER_ROTATION = (1024 * 4); 	// CPR is 1024 and multipled by 4 because it is a quadrature encoder
	enum {											// Wrist subsystem movement states
		WRIST_NOCHANGE = -1,						// No change in wrist angle--maintain current position
		WRIST_FLAT = 0,								// Move to flat floor position
		WRIST_DELIVER = 1,							// Move to delivery angle
		WRIST_STOWED = 2,							// Move to stowed angle (up)
		WRIST_SMARTDASH = 3,						// Move to an angle read from dashboard
		BUMP_ANGLE = 4								// Move by bumping angle up or down
	};

	int				m_wristLevel;					// Current wrist level (FLAT, STOWED, etc--not degrees)
	double			m_targetDegrees;				// Target angle of degrees that are requested of the wrist
	double			m_targetCounts;					// Target encoder counts of angle that are requested of the wrist
	double			m_curDegrees;
	bool			m_bumpDir;						// State variable for bumping up or down

	Timer			m_safetyTimer;					// Safety timer for use in Wrist
	double			m_safetyTimeout;				// Seconds that the timer ran before stopping

	// Configuration file parameters
	double 			m_pidSpeed;						// Wrist maximum speed during movement
	double			m_pidKp;						// Wrist PID proportional constant
	int				m_pidAllowableCLE;				// Wrist PID allowable closed loop error
	int				m_wristMaxCounts;				// Wrist maximum allowable counts
	int				m_wristMinCounts;				// Wrist minimum allowable counts
	double			m_offsetDegrees;				// Wrist offset to flat position in degrees
	double			m_bumpAngle;					// Incremental angle when bumping the wrist up/down
	double			m_flatAngle;					// Setpoint for floor level (full down)
	double			m_deliveryAngle;				// Setpoint to deliver to switch
	double			m_stowedAngle;					// Setpoint for full up

public:
	Wrist();
	void InitDefaultCommand() override;
	void Initialize(frc::Preferences *RobotConfig);
	void Periodic() override;
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

	double DegreesToCounts(double degrees);
	double CountsToDegrees(int counts);
	double GetCurrentDegrees();

	void MoveToPosition(int angle);
	bool MoveToPositionIsFinished(void);
	void MoveToPositionStop(void);
	void BumpToPosition(bool direction);
};

#endif
