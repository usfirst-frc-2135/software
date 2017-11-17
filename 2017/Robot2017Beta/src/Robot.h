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

class Robot : public frc::TimedRobot {
public:
	std::unique_ptr<frc::Command> autonomousCommand;
	static std::unique_ptr<OI> oi;
	frc::LiveWindow *lw = frc::LiveWindow::GetInstance();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    static std::shared_ptr<Chassis> chassis;
    static std::shared_ptr<Intake> intake;
    static std::shared_ptr<Agitator> agitator;
    static std::shared_ptr<Shooter> shooter;
    static std::shared_ptr<Delivery> delivery;
    static std::shared_ptr<Climber> climber;
    static std::shared_ptr<Pneumatics> pneumatics;
    static std::shared_ptr<Power> power;
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	void RobotInit() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
	void TestPeriodic() override;
};
#endif
