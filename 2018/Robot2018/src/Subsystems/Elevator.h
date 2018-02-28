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
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../RobotDefaults.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Elevator: public frc::Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
#if !defined (ROBORIO_STANDALONE) || defined (ROBOTBENCHTOPTEST)
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<WPI_TalonSRX> motorL7;
	std::shared_ptr<WPI_TalonSRX> motorR8;
	std::shared_ptr<frc::DigitalInput> hallLimit;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
#endif

	const int		m_slotIndex = 0;				// Motor controller profile slot index
	const int 		m_pidIndex = 0; 				// PID Slot index for sensors
	const int		m_timeout = 10;					// CAN timeout in msec to wait for response
	const double 	COUNTS_PER_ROTATION = (1024*4);	// CPR is 1024 and multipled by 4 because it is a quadrature encoder
	enum { NOCHANGE_HEIGHT=-1, FLOOR_HEIGHT=0, SWITCH_HEIGHT=1, SCALE_LO_HEIGHT=2, SCALE_HI_HEIGHT=3, CLIMB_HEIGHT=4, LEVITATE_HEIGHT=5, SMARTDASH_HEIGHT=6, BUMP_HEIGHT=7 };
	enum { CALIB_START, CALIB_MOVE_UP, CALIB_START_DOWN, CALIB_MOVE_DOWN, CALIB_DONE };

	double			m_targetInches;					// Target inches of height that are requested of the elevator
	double			m_targetCounts;					// Target encoder counts of height that are requested of the elevator
	double			m_curInches;
	bool			m_calibrated;					// Indicates whether the elevator has been calibrated
	int				m_calibrationState;				// State variable for calibration sequence
	bool			m_bumpDir;						// State variable for bumping up or down

	Timer			m_safetyTimer;					// Safety timer for use in elevator
	double			m_safetyTimeout;				// Seconds that the timer ran before stopping

	// Configuration file parameters
	double			m_calibrationSpeed;				// Motor output speed used during calibration
	double 			m_pidSpeed;				// Elevator maximum speed during movement
	double			m_pidKp;						// Elevator PID proportional constant
	int				m_pidAllowableCLE;				// Elevator PID allowable closed loop error
	double			m_elevatorMaxHeight;			// Elevator maximum allowable height
	double			m_elevatorMinHeight;			// Elevator minimum allowable height
	double			m_bumpHeight;					// Incremental height when bumping the elevator up/down
	double			m_floorHeight;					// Setpoint for floor level (full down)
	double			m_switchHeight;					// Setpoint to deliver to switch
	double			m_scaleLoHeight;				// Setpoint for delivery to scale when low
	double			m_scaleHiHeight;				// Setpoint for delivery to scale when high
	double			m_climbHeight;					// Setpoint for lining up to climb
	double			m_levitateHeight;				// Setpoint for a valid levitation

#ifdef ROBOTBENCHTOPTEST
	const double 	m_circumInches = (1.875*M_PI*2);		//Circumference in inches for Benchtop Testing
#else
	const double 	m_circumInches = (1.273*M_PI);		//Circumference in inches (Real Robot)
#endif

public:
	Elevator();
	void InitDefaultCommand() override;
	void Periodic() override;
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

	double InchesToCounts(double inches);
	double CountsToInches(int counts);
	double GetCurrentInches();
	bool HallSensorIsTriggered(void);

	void MoveToPosition(int height);
	bool MoveToPositionIsFinished(void);
	void MoveToPositionStop(void);

	void BumpToPosition(bool direction);

	void CalibrationInit(void);
	void CalibrationExecute(void);
	bool CalibrationIsFinished(void);
	void CalibrationOverride(void);
};

#endif
