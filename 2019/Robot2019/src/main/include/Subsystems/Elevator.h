// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "frc/commands/Subsystem.h"
#include "frc/WPILib.h"
#include "ctre/Phoenix.h"

#include "RobotDefaults.h"
#include "frc2135/TalonSRXUtils.h"
#include "frc2135/RobotConfig.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Elevator: public frc::Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<WPI_TalonSRX> motorEL7;
	std::shared_ptr<WPI_TalonSRX> motorEL8;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	// Constants
	bool			m_elevatorDebug = false;		// Debug flag to disable extra logging calls
	const int		m_slotIndex = 0;				// Motor controller profile slot index
	const int 		m_pidIndex = 0; 				// PID Slot index for sensors
	const int		m_timeout = 30;					// CAN timeout in msec to wait for response
	const double	COUNTS_PER_ROTATION = (1024*4);	// CPR is 1024 and multipled by 4 because it is a quadrature encoder

	enum {							// Calibration procedure states
		CALIB_START, 				//	Start by preparing to move upward
		CALIB_MOVE_UP, 				//	Keep moving up away from (triggered) hall sensor
		CALIB_START_DOWN, 			//	Prepare to move down toward hall sensor
		CALIB_MOVE_DOWN, 			//	Monitor for hall sensor before moving to done state
		CALIB_DONE
	};

	bool m_talonValidEL7;				// Health indicator for Elevator Talon 7
	bool m_talonValidEL8;				// Health indicator for Elevator Talon 8

	int				m_elevatorLevel;				// Current elevator level (FLOOR, SCALE, etc--not inches)
	double			m_targetInches;					// Target inches of height that are requested of the elevator
	int				m_targetCounts;					// Target encoder counts of height that are requested of the elevator
	double			m_curInches;
	bool			m_calibrated;					// Indicates whether the elevator has been calibrated
	int				m_calibrationState;				// State variable for calibration sequence
	bool			m_bumpDir;						// State variable for bumping up or down
	bool 			m_isCargo; 						// True - Game Piece is cargo, False - Game Piece is hatch

	frc::Timer		m_safetyTimer;					// Safety timer for use in elevator
	double			m_safetyTimeout;				// Seconds that the timer ran before stopping

	// Configuration file parameters
	double			m_calibrationSpeed;				// Motor output speed used during calibration
	double 			m_pidMaxOut;					// Elevator maximum speed during movement
	double			m_pidKp;						// Elevator PID proportional constant
	double			m_arbFeedForward;				// Elevator Motion Magic Arbitrary Feed Forward		
	int				m_CLAllowedError;				// Elevator PID allowable closed loop error
	double			m_toleranceInches;				// Elevator PID tolerance in inches
	double			m_CLRampRate;					// Elevator PID ramp rate

	double			m_elevatorMaxHeight;			// Elevator maximum allowable height
	double			m_elevatorMinHeight;			// Elevator minimum allowable height
	double			m_lowGearHeight;				// Height for forcing drivetrain to low gear
	double			m_bumpHeight;					// Incremental height when bumping the elevator up/down
	double			m_groundCargoHeight;			// Setpoint for floor level for cargo (full down)
	double 			m_groundHatchHeight; 			// Set point for floor level for hatch
	double			m_shipCargoHeight;				// Setpoint to deliver cargo in cargo ship
	double			m_shipHatchHeight;				// Setpoint to deliver hatches to rocket at first level
	double			m_rocketL1CargoHeight;			// Setpoint for delivery of cargo to rocket at first level
	double 			m_rocketL1HatchHeight; 			// Setpoint for delivery of hatch to rocket at first level
	double 			m_rocketL2CargoHeight; 			// Setpoint for delivery of cargo to rocket at second level 
	double			m_rocketL2HatchHeight;			// Setpoint for delivery of hatch to rocket at second level
	double 			m_rocketL3CargoHeight;			// Setpoint for delivery of cargo to rocket at third level 
	double			m_rocketL3HatchHeight;			// Setpoint for delivery of hatch to rocket at third level

	const double 	m_circumInches = (1.751*M_PI);	// Circumference in inches 

public:
	Elevator();
	void InitDefaultCommand() override;
	void Periodic() override;
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

enum {								// Elevator subsystem movement states
		NOCHANGE_HEIGHT = -1,		//	No change in height--maintain current position
		GROUND_HEIGHT = 0,			//	Move to ground height
		SHIP_HEIGHT = 1,			//	Move to cargo ship height
		ROCKET_L1_HEIGHT = 2,		//	Move to rocket level 1 height
		ROCKET_L2_HEIGHT = 3, 		//	Move to rocket level 2 height
		ROCKET_L3_HEIGHT = 4,		//	Move to rocket level 3 height
		SMARTDASH_HEIGHT = 5,		//	Move to a height prescribed on dashboard (debug only)
		BUMP_HEIGHT = 6				//	Move by bumping height up or down
	};

	void Initialize(void);
	void FaultDump(void);

	int InchesToCounts(double inches);
	double CountsToInches(int counts);
	double GetCurrentInches();

	void MoveToPositionInit(int height);
	bool MoveToPositionIsFinished(void);
	void BumpToPosition(bool direction);

	void CalibrationOverride(void);

	void SetGamePiece(bool setting);

};

#endif
