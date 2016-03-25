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
#include "Commands/DriveStop.h"
#include "Commands/DriveDistanceDelayed.h"
#include "Commands/DriveDistanceTimed.h"


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
std::shared_ptr<Chassis> Robot::chassis;
std::shared_ptr<Sweeper> Robot::sweeper;
std::shared_ptr<Shooter> Robot::shooter;
std::shared_ptr<Climber> Robot::climber;
std::shared_ptr<Pneumatics> Robot::pneumatics;
std::unique_ptr<OI> Robot::oi;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION

void Robot::RobotInit() {
	RobotMap::init();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    chassis.reset(new Chassis());
    sweeper.reset(new Sweeper());
    shooter.reset(new Shooter());
    climber.reset(new Climber());
    pneumatics.reset(new Pneumatics());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi.reset(new OI());

	// instantiate the command used for the autonomous period
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	autonomousCommand.reset(new AutonomousCommand());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS


	// Initialize preferences file on roboRio
	prefs = Preferences::GetInstance();

	//Initialize SmartDashboard and Subsystems
	chassis->Initialize(prefs);
	sweeper->Initialize(prefs);
	shooter->Initialize(prefs);
	climber->Initialize(prefs);
	pneumatics->Initialize(prefs);

	// Build and display autoChooser
	chooser = new SendableChooser();
	chooser->AddDefault("Sit still", (void*) SITSTILL);
	chooser->AddObject("Drive distance", (void*) DRIVEDISTANCE);
	chooser->AddObject("Drive timed", (void*) DRIVETIMED);
	SmartDashboard::PutData("Auto Mode Chooser", chooser);

	// Display scheduler status
//	SmartDashboard::PutData(Scheduler::GetInstance());
//	SmartDashboard::PutData(chassis.get());
//	SmartDashboard::PutData(sweeper);
//	SmartDashboard::PutData(shooter);
//	SmartDashboard::PutData(climber);
//	SmartDashboard::PutData(pneumatics);

	printf("2135: Building autonomous chooser complete\n");

	// Start up the camera
//	CameraServer::GetInstance()->StartAutomaticCapture("cam1");
}

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit() {
	printf("2135: DisabledInit Running\n");
	if (autonomousCommand.get() != nullptr)
				autonomousCommand->Cancel();
}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	printf("2135: Starting Autonomous Command\n");
	switch((int)(chooser->GetSelected())) {
		default:
		case SITSTILL: autonomousCommand.reset(new DriveStop); break;
		case DRIVEDISTANCE: autonomousCommand.reset(new DriveDistanceDelayed(0.0, 0.0, 0.0)); break;
		case DRIVETIMED: autonomousCommand.reset(new DriveDistanceTimed(15, 0.75)); break;
	}
	if (autonomousCommand.get() != nullptr) {
		autonomousCommand->Start();
		printf("2135: Autonomous Command Started\n");
	}
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {
	lw->Run();
}

double Robot::LoadPreferencesVariable(std::string name, double defaultValue) {
	Preferences	*prefs;
	double 		value;

	prefs = Preferences::GetInstance();

	if (prefs->ContainsKey(name)) {
		value = prefs->GetDouble(name, defaultValue);
	}
	else {
		value = defaultValue;
		printf("2135: ERROR - %s not found\n", name.c_str());
	}
	printf("2135: %15s : %f\n", name.c_str(), value);

	return value;
}

START_ROBOT_CLASS(Robot);

