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
	std::shared_ptr<WPI_TalonSRX> motorL7;
	std::shared_ptr<WPI_TalonSRX> motorR8;
	std::shared_ptr<frc::DigitalInput> hallLimit;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	//	Declare constants
	const bool		m_elevatorDebug = false;		// Debug flag to disable extra logging calls
	const int		m_slotIndex = 0;				// Motor controller profile slot index
	const int 		m_pidIndex = 0; 				// PID Slot index for sensors
	const int		m_timeout = 10;					// CAN timeout in msec to wait for response
	const double	COUNTS_PER_ROTATION = (1024*4);	// CPR is 1024 and multipled by 4 because it is a quadrature encoder
	enum {							// Calibration procedure states
		CALIB_START, 				//	Start by preparing to move upward
		CALIB_MOVE_UP, 				//	Keep moving up away from (triggered) hall sensor
		CALIB_START_DOWN, 			//	Prepare to move down toward hall sensor
		CALIB_MOVE_DOWN, 			//	Monitor for hall sensor before moving to done state
		CALIB_DONE
	};

	bool			m_talonValidL7;					// Health indicator for elevator Talon Left 7
	bool			m_talonValidR8;					// Health indicator for elevator Talon Right 8

	int				m_elevatorLevel;				// Current elevator level (FLOOR, SCALE, etc--not inches)
	double			m_targetInches;					// Target inches of height that are requested of the elevator
	int				m_targetCounts;					// Target encoder counts of height that are requested of the elevator
	double			m_curInches;
	bool			m_calibrated;					// Indicates whether the elevator has been calibrated
	int				m_calibrationState;				// State variable for calibration sequence
	bool			m_bumpDir;						// State variable for bumping up or down

	frc::Timer			m_safetyTimer;					// Safety timer for use in elevator
	double			m_safetyTimeout;				// Seconds that the timer ran before stopping

	// Configuration file parameters
	double			m_calibrationSpeed;				// Motor output speed used during calibration
	double 			m_pidMaxOut;						// Elevator maximum speed during movement
	double			m_pidKp;						// Elevator PID proportional constant
	int				m_CLAllowedError;				// Elevator PID allowable closed loop error
	double			m_toleranceInches;				// Elevator PID tolerance in inches
	double			m_CLRampRate;					// Elevator PID ramp rate
	double			m_elevatorMaxHeight;			// Elevator maximum allowable height
	double			m_elevatorMinHeight;			// Elevator minimum allowable height
	double			m_bumpHeight;					// Incremental height when bumping the elevator up/down
	double			m_floorHeight;					// Setpoint for floor level (full down)
	double			m_switchHeight;					// Setpoint to deliver to switch
	double			m_scaleLoHeight;				// Setpoint for delivery to scale when low
	double			m_scaleHiHeight;				// Setpoint for delivery to scale when high
	double			m_climbHeight;					// Setpoint for lining up to climb
	double			m_levitateHeight;				// Setpoint for a valid levitation
	double			m_lowGearHeight;				// Height for forcing drivetrain to low gear

	const double 	m_circumInches = (1.273*M_PI);	//Circumference in inches (Real Robot)

public:
	Elevator();
	void InitDefaultCommand() override;
	void Periodic() override;

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

	enum {							// Elevator subsystem movement states
		NOCHANGE_HEIGHT = -1,		//	No change in height--maintain current position
		FLOOR_HEIGHT = 0,			//	Move to floor (full down) height
		SWITCH_HEIGHT = 1,			//	Move to switch height
		SCALE_LO_HEIGHT = 2,		//	Move to scale low height (4-5ft)
		SCALE_HI_HEIGHT = 3,		//	Move to scale high height (6ft)
		CLIMB_HEIGHT = 4,			//	Move to climb height to approach run
		LEVITATE_HEIGHT = 5,		//	Move to levitate height to lift robot
		SMARTDASH_HEIGHT = 6,		//	Move to a height prescribed on dashboard (debug only)
		BUMP_HEIGHT = 7,			//	Move by bumping height up or down
		REQUESTED_HEIGHT = 11		//  Move to requested height (set within MoveToPosition function)
	};

	void Initialize(void);

	int InchesToCounts(double inches);
	double CountsToInches(int counts);
	double GetCurrentInches();
	bool HallSensorIsTriggered(void);
	bool HeightLimitToLowGear(void);

	void MoveToPosition(int height);
	bool MoveToPositionIsFinished(void);
	void BumpToPosition(bool direction);

	void CalibrationInit(void);
	void CalibrationExecute(void);
	bool CalibrationIsFinished(void);
	void CalibrationStop(void);
	void CalibrationOverride(void);

};

#endif
