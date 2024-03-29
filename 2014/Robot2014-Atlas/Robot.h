// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#ifndef _ROBOT_H
#define _ROBOT_H
#include "WPILib.h"
#include "Commands/Command.h"
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Subsystems/BallGate.h"
#include "Subsystems/Chassis.h"
#include "Subsystems/Pneumatics.h"
#include "Subsystems/Shooter.h"
#include "Subsystems/SweeperArm.h"
#include "Subsystems/SweeperMotor.h"
#include "Subsystems/Transmission.h"
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "OI.h"
#define M_PI 3.14159265358979323846
class Robot : public IterativeRobot {
public:
	Command *autonomousCommand;
	static OI *oi;
	LiveWindow *lw;
	SendableChooser		*autoChooser;
	DriverStationLCD	*ds;
	Preferences			*prefs;
	double 				m_autoSetpoint;
	double 				m_pidMaxOutput;
	double 				m_sweeperSpeed;
	double 				m_shooterSpeed;
	double				m_chassisMinRange;
	double 				m_chassisMaxRange;
	std::string			m_autoDefault;
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	static Chassis* chassis;
	static Transmission* transmission;
	static SweeperArm* sweeperArm;
	static SweeperMotor* sweeperMotor;
	static Shooter* shooter;
	static BallGate* ballGate;
	static Pneumatics* pneumatics;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	virtual void RobotInit();
	virtual void AutonomousInit();
	virtual void AutonomousPeriodic();
	virtual void TeleopInit();
	virtual void TeleopPeriodic();
	virtual void DisabledInit();
	virtual void DisabledPeriodic();
	virtual void TestPeriodic();
	void UpdateSmartDashboard();
	void InitSmartDashboard();
};
#endif
