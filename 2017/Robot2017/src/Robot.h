// RobotBuilder Version: 2.0
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
#include "LiveWindow/LiveWindow.h"
#include "RobotDefaults.h"
#include "RobotMap.h"
#include "frc2135/GripContoursPipeline.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Subsystems/Agitator.h"
#include "Subsystems/Chassis.h"
#include "Subsystems/Climber.h"
#include "Subsystems/Delivery.h"
#include "Subsystems/Intake.h"
#include "Subsystems/Pneumatics.h"
#include "Subsystems/Power.h"
#include "Subsystems/Shooter.h"

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

#include "OI.h"

class Robot : public IterativeRobot {
public:
	std::unique_ptr<Command> autonomousCommand;
	frc::SendableChooser<frc::Command*> chooser;

	static std::unique_ptr<OI> oi;
	frc::LiveWindow *lw = frc::LiveWindow::GetInstance();
	Preferences *prefs = Preferences::GetInstance();

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    static std::shared_ptr<Chassis> chassis;
    static std::shared_ptr<Intake> intake;
    static std::shared_ptr<Agitator> agitator;
    static std::shared_ptr<Shooter> shooter;
    static std::shared_ptr<Delivery> delivery;
    static std::shared_ptr<Climber> climber;
    static std::shared_ptr<Pneumatics> pneumatics;
//    static std::shared_ptr<Power> power;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	virtual void RobotInit();
	virtual void DisabledInit();
	virtual void DisabledPeriodic();
	virtual void AutonomousInit();
	virtual void AutonomousPeriodic();
	virtual void TeleopInit();
	virtual void TeleopPeriodic();
	virtual void TestPeriodic();

	static double LoadPreferencesVariable(std::string name, double defaultValue);

private:
	bool m_faultsCleared;
	// Smartdashboard update rates in 20ms packet counts
#define	SMARTDBD_PKTRATE			20			// 20 ms - period of every packet from driver station
#define SMARTDBD_FASTRATE			200			// 200 ms
#define SMARTDBD_SLOWRATE			500			// 500 ms
	static int const smartdashDisabledRate = SMARTDBD_FASTRATE/20;		// 200ms
	static int const smartdashTeleopRate = SMARTDBD_SLOWRATE/20;		// 500ms
	static int const smartdashAutonRate = SMARTDBD_SLOWRATE/20;			// 500ms
	static int const smartdashLiveRate = SMARTDBD_SLOWRATE/20;			// 500ms

	void RobotModeInitialize();
	void SmartDashboardStartChooser();
	void SmartDashboardUpdate(int rate);
	void RobotFaultDump(void);
	void RobotFaultDumpTalonSRX(const char *talonName, std::shared_ptr<CAN::TalonSRX> talonPtr);
};

void VisionThread();

#endif
