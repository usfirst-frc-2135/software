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
	int 			m_wristDebug = 0; 				// Debug flag to disable extra logging calls
	const int 		m_slotIndex = 0;				// Motor controller profile slot index
	const int 		m_pidIndex = 0; 				// PID Slot index for sensors
	const int 		m_timeout = 30;					// CAN timeout in msec to wait for response
	const double	OUTPUT_SHAFT_REDUCTION = ((double)22/(double)16);	// Sprocket reduction on output shaft 16T to 22T sprockets
	const double 	COUNTS_PER_ROTATION = (1024 * 4); 	// CPR is 1024 and multipled by 4 because it is a quadrature encoder
   
    bool			m_talonValidWR12;				// Health indicator for wrist Talon 12

	bool			m_calibrated;					// Indicates whether the elevator has been calibrated
	int				m_wristLevel;					// Current wrist level (not degrees)
	double			m_targetDegrees;				// Target angle of degrees that are requested of the wrist
	int				m_targetCounts;					// Target encoder counts of angle that are requested of the wrist
	double			m_curDegrees;
	bool			m_bumpDir;						// State variable for bumping up or down

	frc::Timer		m_safetyTimer;					// Safety timer for use in Wrist
	double			m_safetyTimeout;				// Seconds that the timer ran before stopping

	bool 			m_isCargo; 						// True - Game Piece is cargo, False - Game Piece is hatch

	// Configuration file parameters
	double 			m_pidMaxOut;					// Wrist maximum speed during movement
	int				m_velocity;						// Wrist motion velocity
	int				m_acceleration;					// Wrist motion acceleration
	int				m_sCurveStrength;				// Wrist motion S curve smoothing strength
	double			m_pidKf;						// Wrist PID force constant
	double			m_pidKp;						// Wrist PID proportional constant
	double			m_pidKi;						// Wrist PID integral constant
	double			m_pidKd;						// Wrist PID derivative constant
	double			m_arbFeedForward;				// Wrist Motion Magic Arbitrary Feed Forward		
	double			m_toleranceDegrees;				// Wrist PID tolerance in degrees	
	int				m_wristMaxCounts;				// Wrist maximum allowable counts
	int				m_wristMinCounts;				// Wrist minimum allowable counts
	double			m_bumpAngle;					// Incremental angle when bumping the wrist up/down

	double			m_groundCargoAngle;				// Setpoint for floor level (tilted for cargo pickup)
	double			m_groundHatchAngle;				// Setpoint for floor level (full down for hatch pickup)
	double			m_shipCargoAngle;				// Setpoint to deliver cargo in cargo ship
	double			m_shipHatchAngle;				// Setpoint to deliver hatches to rocket at first level
	double			m_rocketL1CargoAngle;			// Setpoint for delivery of cargo to rocket at first level
	double 			m_rocketL1HatchAngle; 			// Setpoint for delivery of hatch to rocket at first level
	double 			m_rocketL2CargoAngle; 			// Setpoint for delivery of cargo to rocket at second level 
	double			m_rocketL2HatchAngle;			// Setpoint for delivery of hatch to rocket at second level
	double 			m_rocketL3CargoAngle;			// Setpoint for delivery of cargo to rocket at third level 
	double			m_rocketL3HatchAngle;			// Setpoint for delivery of hatch to rocket at third level
	double 			m_stowedAngle;

public:
	Wrist();
	void InitDefaultCommand() override;
	void Periodic() override;
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
	
	enum {									// Wrist subsystem movement states
		NOCHANGE_ANGLE = -1,				// No change in wrist angle--maintain current position
		GROUND_ANGLE = 0,					// Move to ground angle
		SHIP_ANGLE = 1,						// Move to cargo ship angle
		ROCKET_L1_ANGLE = 2,				// Move to rocket level 1 angle		
		ROCKET_L2_ANGLE = 3, 				// Move to rocket level 2 angle
		ROCKET_L3_ANGLE = 4,				// Move to rocket level 3 angle
		SMARTDASH_ANGLE = 5,				// Move to an angle read from dashboard
		BUMP_ANGLE = 6,						// Move by bumping angle up or down
		STOW_ANGLE = 7
	};

	void Initialize(void);
	void FaultDump(void);

	int DegreesToCounts(double degrees);
	double CountsToDegrees(int counts);
	double GetCurrentDegrees();

	void MoveToPositionInit(int level);
	bool MoveToPositionIsFinished(void);
	void BumpToPosition(bool direction);

	void Calibrate();

	void SetGamePiece(bool setting);

};

#endif
