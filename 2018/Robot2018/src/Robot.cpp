// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Robot.h"

#include "RobotConfig.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
std::shared_ptr<Drivetrain> Robot::drivetrain;
std::shared_ptr<Gripper> Robot::gripper;
std::shared_ptr<Elevator> Robot::elevator;
std::unique_ptr<OI> Robot::oi;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION

void Robot::RobotInit() {
	RobotMap::init();
	std::printf("2135: RobotInit\n");

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    drivetrain.reset(new Drivetrain());
    gripper.reset(new Gripper());
    elevator.reset(new Elevator());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi.reset(new OI());

	// Add commands to Autonomous Sendable Chooser
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS

	chooser.AddObject("Auto Stop", new AutoStop());
	chooser.AddObject("Auto Drive Distance", new AutoDriveDistance());
	chooser.AddObject("Auto Drive Turn", new AutoDriveTurn());

	chooser.AddDefault("Drive Stop", new DriveStop());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	frc::SmartDashboard::PutData("Auto Modes", &chooser);

}

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit(){

}

void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	// Initializes the gameData that read switch and scale colors from the FMS
	std::string gameData;
	gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();

	// Chooser that reads switch and scale colors from the FMS
	if(gameData[0] == 'L') // Reads switch closest to Alliance Station
	{
		std::printf("2135: Autonomous Level 1 Switch Left Side \n");
	} else {
		std::printf("2135: Autonomous Level 1 Switch Right Side \n");

	}

	if(gameData[1] == 'L') // Reads scale
	{
		std::printf("2135: Autonomous Level 2 Scale Left Side \n");
	} else {
		std::printf("2135: Autonomous Level 2 Scale Right Side \n");
	}

	if(gameData[2] == 'L') // Reads switch farthest from the Alliance Station
	{
		std::printf("2135: Autonomous Level 3 Switch Left Side \n");
	} else {
		std::printf("2135: Autonomous Level 3 Switch Right Side \n");
	}

	autonomousCommand = chooser.GetSelected();
	if (autonomousCommand != nullptr)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	if (autonomousCommand != nullptr)
		autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

START_ROBOT_CLASS(Robot);
