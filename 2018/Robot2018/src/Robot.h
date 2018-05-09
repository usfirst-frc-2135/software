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
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "RobotDefaults.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Commands/AutoStop.h"
#include "Commands/AutoPosANYMove.h"
#include "Commands/AutoPos1.h"
#include "Commands/AutoPos2.h"
#include "Commands/AutoPos3.h"
#include "Subsystems/Drivetrain.h"
#include "Subsystems/Elevator.h"
#include "Subsystems/Gripper.h"
#include "Subsystems/Pneumatics.h"
#include "Subsystems/Wrist.h"


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "OI.h"

class Robot : public frc::TimedRobot {
public:
	frc::Command* autonomousCommand = nullptr;

	static std::unique_ptr<OI> oi;
	frc::LiveWindow *lw = frc::LiveWindow::GetInstance();
	static frc::SendableChooser<frc::Command*>* chooser;
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	static std::shared_ptr<Drivetrain> drivetrain;
	static std::shared_ptr<Elevator> elevator;
	static std::shared_ptr<Gripper> gripper;
	static std::shared_ptr<Wrist> wrist;
	static std::shared_ptr<Pneumatics> pneumatics;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	void RobotInit() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;

	static void SmartDashboardStartChooser(void);


private:
	enum fmsSide_t { SIDE_UNINIT, SIDE_UNKNOWN, SIDE_LEFT, SIDE_RIGHT };
	const char *FMS_Left = "LEFT";
	const char *FMS_Right = "RIGHT";
	const char *FMS_Unknown = "UNKNOWN";
	const char *FMS_Uninit = "UNINIT";
	fmsSide_t m_FMSAlliSwitch;
	fmsSide_t m_FMSScale;
	fmsSide_t m_FMSOppSwitch;
	bool m_faultsCleared;

	fmsSide_t FMSGameDataSide(char c);
	const char *FMSGameDataString(fmsSide_t side);
	void FMSGameDataRead(void);

	void RobotFaultDump(void);
	void RobotFaultDumpTalonSRX(const char *talonName, std::shared_ptr<WPI_TalonSRX> talonPtr);
};
#endif
