// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "Robot.h"
#include "DriverStationLCD.h"
#include "Commands\DriveStop.h"
#define M_PI 3.14159265358979323846
SendableChooser* autoChooser;
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
Chassis* Robot::chassis = 0;
Transmission* Robot::transmission = 0;
SweeperArm* Robot::sweeperArm = 0;
SweeperMotor* Robot::sweeperMotor = 0;
Shooter* Robot::shooter = 0;
TriggerShooter* Robot::triggerShooter = 0;
BallGate* Robot::ballGate = 0;
Pneumatics* Robot::pneumatics = 0;
OI* Robot::oi = 0;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
void Robot::RobotInit() {
	DriverStationLCD* ds = DriverStationLCD::GetInstance();
	printf( "\n2135: Atlas RobotInit - " __DATE__" "__TIME__"\n" );
	ds->PrintfLine(DriverStationLCD::kUser_Line1, "Atlas 2014");
	ds->UpdateLCD();
	RobotMap::init();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	chassis = new Chassis();
	transmission = new Transmission();
	sweeperArm = new SweeperArm();
	sweeperMotor = new SweeperMotor();
	shooter = new Shooter();
	triggerShooter = new TriggerShooter();
	ballGate = new BallGate();
	pneumatics = new Pneumatics();
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi = new OI();
	lw = LiveWindow::GetInstance();
	// instantiate the command used for the autonomous period
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	autonomousCommand = new AutoCommand();
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	SmartDashboard::PutNumber("L: P", chassis->leftDrivePID->GetP());
	SmartDashboard::PutNumber("L: I", chassis->leftDrivePID->GetI());
	SmartDashboard::PutNumber("L: D", chassis->leftDrivePID->GetD());
	SmartDashboard::PutNumber("L: Tolerance", 0.2);
	SmartDashboard::PutNumber("L: Min Output", -0.6);
	SmartDashboard::PutNumber("L: Max Output", 0.6);
	SmartDashboard::PutNumber("L: Distance PP", 4 * M_PI / 360);
	SmartDashboard::PutNumber("L: Distance", chassis->leftDriveEncoder->GetDistance());
	SmartDashboard::PutNumber("R: P", chassis->rightDrivePID->GetP());
	SmartDashboard::PutNumber("R: I", chassis->rightDrivePID->GetI());
	SmartDashboard::PutNumber("R: D", chassis->rightDrivePID->GetD());
	SmartDashboard::PutNumber("R: Tolerance", 0.2);
	SmartDashboard::PutNumber("R: Min Output", -0.6);
	SmartDashboard::PutNumber("R: Max Output", 0.6);
	SmartDashboard::PutNumber("R: Distance PP", 4 * M_PI / 360);
	SmartDashboard::PutNumber("R: Distance", chassis->rightDriveEncoder->GetDistance());
	SmartDashboard::PutNumber("Target Setpoint", 66.0);
	SmartDashboard::PutNumber("Left Setpoint", 0.0);
	SmartDashboard::PutNumber("Right Setpoint", 0.0);
	SmartDashboard::PutNumber("Sweeper Speed", 1.0);
	SmartDashboard::PutNumber("Shooter Speed", 1.0);
	
	autoChooser = new SendableChooser();
	autoChooser->AddDefault( "Move forward", new AutoCommand() );
	autoChooser->AddObject( "Sit still", new DriveStop() );
	SmartDashboard::PutData( "Auto Mode Chooser", autoChooser );
}
	
void Robot::AutonomousInit() {
	printf( "2135: Autonomous Init\n" );
	if (autonomousCommand != NULL)
		autonomousCommand->Start();
}
	
void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
	SmartDashboard::PutNumber("L: Distance", Robot::chassis->leftDriveEncoder->GetDistance());
	SmartDashboard::PutNumber("R: Distance", -Robot::chassis->rightDriveEncoder->GetDistance());
}
	
void Robot::TeleopInit() {
	printf( "2135: Teleop Init\n" );
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to 
	// continue until interrupted by another command, remove
	// this line or comment it out.
	autonomousCommand->Cancel();
}
	
void Robot::TeleopPeriodic() {
	if (autonomousCommand != NULL)
		Scheduler::GetInstance()->Run();
	SmartDashboard::PutNumber("L: Distance", Robot::chassis->leftDriveEncoder->GetDistance());
	SmartDashboard::PutNumber("R: Distance", -Robot::chassis->rightDriveEncoder->GetDistance());
}
void Robot::TestPeriodic() {
	lw->Run();
}
START_ROBOT_CLASS(Robot);
