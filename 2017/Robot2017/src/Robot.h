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
#include "GripContoursPipeline.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Commands/AutonDefault.h"
#include "Subsystems/Agitator.h"
#include "Subsystems/Chassis.h"
#include "Subsystems/Climber.h"
#include "Subsystems/Delivery.h"
#include "Subsystems/Intake.h"
#include "Subsystems/Pneumatics.h"
#include "Subsystems/Shooter.h"


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "OI.h"

class Robot : public IterativeRobot {
public:
	std::unique_ptr<Command> autonomousCommand;
	static std::unique_ptr<OI> oi;
	LiveWindow *lw = LiveWindow::GetInstance();
	Preferences *prefs = Preferences::GetInstance();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    static std::shared_ptr<Chassis> chassis;
    static std::shared_ptr<Intake> intake;
    static std::shared_ptr<Agitator> agitator;
    static std::shared_ptr<Shooter> shooter;
    static std::shared_ptr<Delivery> delivery;
    static std::shared_ptr<Climber> climber;
    static std::shared_ptr<Pneumatics> pneumatics;

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

	Robot();

	std::shared_ptr<NetworkTable> table;

private:
	static int const imgWidth = 320;
	static int const imgHeight = 240;

	std::thread visionThread;
	static void CameraVisionThread();
	static float CalcDistToTarget(const float& rectWidthInches, const float& FOVPixels, const float& rectWidthPixels);
	static float CalcCenteringAngle(const cv::Rect& rect, bool& turnRight, const float& imgWidthScreen, const float& distToTarget, const float& RectWidthInches);
};
#endif
