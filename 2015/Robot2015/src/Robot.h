// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.
#ifndef _ROBOT_H
#define _ROBOT_H

#include "WPILib.h"
#include "Commands/Command.h"
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Commands/AutoCommand.h"
#include "Subsystems/Chassis.h"
#include "Subsystems/Elevator.h"
#include "Subsystems/HWheel.h"
#include "Subsystems/Intake.h"
#include "Subsystems/Pneumatics.h"
#include "Subsystems/Stacker.h"


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "OI.h"

class Robot : public IterativeRobot {
public:
	Command *autonomousCommand;
	static OI *oi;
	LiveWindow *lw;

	SendableChooser		*autoChooser;

	Preferences		*prefs;
	double			m_autoSetpoint;
	double			m_drivePidMax;
	double          m_drivePidMin;
	double          m_spinTurnSpeed;
	double          m_elevatorSpeed;
	double			m_elevatorPidMin;
	double			m_elevatorPidMax;
	double			m_chassisMinRange;
	double			m_chassisMaxRange;

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	static Chassis* chassis;
	static HWheel* hWheel;
	static Intake* intake;
	static Stacker* stacker;
	static Elevator* elevator;
	static Pneumatics* pneumatics;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	virtual void RobotInit();
	virtual void DisabledInit();
	virtual void DisabledPeriodic();
	virtual void AutonomousInit();
	virtual void AutonomousPeriodic();
	virtual void TeleopInit();
	virtual void TeleopPeriodic();
	virtual void TestPeriodic();

	void InitSmartDashboard();
	void UpdateSmartDashboard();
};
#endif
