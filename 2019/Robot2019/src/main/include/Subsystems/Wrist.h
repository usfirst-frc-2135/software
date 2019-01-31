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
#include "frc/commands/Subsystem.h"
#include "frc/WPILib.h"
#include "ctre/Phoenix.h"

#include "frc2135/TalonSRXUtils.h"
#include "frc2135/RobotConfig.h"


/**
 *
 *
 * @author ExampleAuthor
 */
class Wrist: public frc::Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<WPI_TalonSRX> motorWR12;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	// Declare constants
	bool 			m_wristDebug = true; 			// Debug flag to disable extra logging calls
	const int 		m_slotIndex = 0;				// Motor controller profile slot index
	const int 		m_pidIndex = 0; 				// PID Slot index for sensors
	const int 		m_timeout = 10;					// CAN timeout in msec to wait for response
	const double	OUTPUT_SHAFT_REDUCTION = ((double)22/(double)16);	// Sprocket reduction on output shaft 16T to 22T sprockets
	const double 	COUNTS_PER_ROTATION = (1024 * 4); 	// CPR is 1024 and multipled by 4 because it is a quadrature encoder
   
    bool			m_talonValidWR12;				// Health indicator for wrist Talon 12

	int				m_wristLevel;					// Current wrist level (not degrees)
	double			m_targetDegrees;				// Target angle of degrees that are requested of the wrist
	int				m_targetCounts;					// Target encoder counts of angle that are requested of the wrist
	double			m_curDegrees;
	bool			m_bumpDir;						// State variable for bumping up or down

	frc::Timer		m_safetyTimer;					// Safety timer for use in Wrist
	double			m_safetyTimeout;				// Seconds that the timer ran before stopping

	// Configuration file parameters
	double 			m_pidMaxOut;					// Wrist maximum speed during movement
	double			m_pidKp;						// Wrist PID proportional constant
	double			m_CLRampRate;					// Wrist PID ramp rate
	int				m_CLAllowedError;				// Wrist PID allowable closed loop error
	double			m_toleranceDegrees;				// Wrist PID tolerance in degrees		
	int				m_wristMaxCounts;				// Wrist maximum allowable counts
	int				m_wristMinCounts;				// Wrist minimum allowable counts
	double			m_bumpAngle;					// Incremental angle when bumping the wrist up/down
	double			m_groundAngle;					// Setpoint for floor level (full down)
	double 			m_stowedAngle; 					// Setpoint for full up
	double 			m_deliveryAngle; 				// Setpoint to deliver to the cargoship or rocket

public:
	Wrist();
	void InitDefaultCommand() override;
	void Periodic() override;
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
	
	enum {											// Wrist subsystem movement states
		WRIST_NOCHANGE = -1,						// No change in wrist angle--maintain current position
		WRIST_GROUND = 0,							// Move to angle facing ground
		WRIST_STOWED = 1,							// Move to stowed angle
		WRIST_DELIVER = 2,							// Move to delivery angle
		WRIST_SMARTDASH = 3,						// Move to an angle read from dashboard
		BUMP_ANGLE = 4								// Move by bumping angle up or down
	};

	void Initialize(void);

	int DegreesToCounts(double degrees);
	double CountsToDegrees(int counts);
	double GetCurrentDegrees();

	void MoveToPosition(int level);
	bool MoveToPositionIsFinished(void);
	void BumpToPosition(bool direction);

	void Calibrate();
};

#endif
