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
#include "Commands\AutoCommand.h"
#include "Commands\AutoDriveAndShoot.h"
#include "Commands\DriveStop.h"
#include "Preferences.h"
#include "CheesyVisionServer.h"
#define M_PI 3.14159265358979323846
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
Chassis* Robot::chassis = 0;
Transmission* Robot::transmission = 0;
SweeperArm* Robot::sweeperArm = 0;
SweeperMotor* Robot::sweeperMotor = 0;
Shooter* Robot::shooter = 0;
BallGate* Robot::ballGate = 0;
Pneumatics* Robot::pneumatics = 0;
OI* Robot::oi = 0;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
void Robot::RobotInit() {
	printf( "\n2135: Atlas RobotInit - " __DATE__" "__TIME__"\n" );
	ds = DriverStationLCD::GetInstance();
	ds->PrintfLine(DriverStationLCD::kUser_Line1, "Atlas 2014");
	ds->UpdateLCD();
	
	RobotMap::init();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	chassis = new Chassis();
	transmission = new Transmission();
	sweeperArm = new SweeperArm();
	sweeperMotor = new SweeperMotor();
	shooter = new Shooter();
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
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	//	Initialize preferences file on cRIO
	prefs = Preferences::GetInstance();
	if (!prefs->ContainsKey( "AutoDriveDistance" )) {
		printf( "2135: AutoDriveDistance Found\n" );
	}
	if (!prefs->ContainsKey( "PidMaxOutput" )) {
		printf( "2135: PidMaxOutput Found\n" );
	}
	if (!prefs->ContainsKey( "SweeperSpeed" )) {
		printf( "2135: SweeperSpeed Found\n" );
	}
	if (!prefs->ContainsKey( "ShooterSpeed" )) {
		printf( "2135: ShooterSpeed Found\n" );
	}
	m_autoSetpoint = prefs->GetDouble( "AutoDriveDistance", 95.0 );
	m_pidMaxOutput = prefs->GetDouble( "PidMaxOutput", 0.6 );
	m_sweeperSpeed = prefs->GetDouble( "SweeperSpeed", 1.0 );
	m_shooterSpeed = prefs->GetDouble( "ShooterSpeed", 0.75 );
	m_autoDefault = prefs->GetString( "AutoDefault", "MoveForward" );
	taskDelay(10);
	printf( "AutodDriveDistance: %f\n", m_autoSetpoint );
	printf( "PidMaxOutput:       %f\n", m_pidMaxOutput );
	printf( "SweeperSpeed:       %f\n", m_sweeperSpeed );
	printf( "ShooterSpeed:       %f\n", m_shooterSpeed );
			
	SmartDashboard::PutNumber("L: P", chassis->leftDrivePID->GetP());
	SmartDashboard::PutNumber("L: I", chassis->leftDrivePID->GetI());
	SmartDashboard::PutNumber("L: D", chassis->leftDrivePID->GetD());
	SmartDashboard::PutNumber("L: Tolerance", 0.2);
	SmartDashboard::PutNumber("L: Min Output", -m_pidMaxOutput);
	SmartDashboard::PutNumber("L: Max Output", m_pidMaxOutput);
	SmartDashboard::PutNumber("L: Distance PP", 4 * M_PI / 360);
	SmartDashboard::PutNumber("L: Distance", chassis->leftDriveEncoder->GetDistance());
	SmartDashboard::PutNumber("R: P", chassis->rightDrivePID->GetP());
	SmartDashboard::PutNumber("R: I", chassis->rightDrivePID->GetI());
	SmartDashboard::PutNumber("R: D", chassis->rightDrivePID->GetD());
	SmartDashboard::PutNumber("R: Tolerance", 0.2);
	SmartDashboard::PutNumber("R: Min Output", -m_pidMaxOutput);
	SmartDashboard::PutNumber("R: Max Output", m_pidMaxOutput);
	SmartDashboard::PutNumber("R: Distance PP", 4 * M_PI / 360);
	SmartDashboard::PutNumber("R: Distance", chassis->rightDriveEncoder->GetDistance());
	SmartDashboard::PutNumber("Target Setpoint", m_autoSetpoint);
	SmartDashboard::PutNumber("Left Setpoint", 0.0);
	SmartDashboard::PutNumber("Right Setpoint", 0.0);
	SmartDashboard::PutNumber("Sweeper Speed", m_sweeperSpeed);
	SmartDashboard::PutNumber("Shooter Speed", m_shooterSpeed);
	
	printf("2135: Building autonomous chooser\n");
	autoChooser = new SendableChooser();
	autoChooser->AddDefault( "Move forward", new AutoCommand() );
	autoChooser->AddObject( "Sit still", new DriveStop() );
	autoChooser->AddObject( "Auto drive and shoot", new AutoDriveAndShoot() );
	SmartDashboard::PutData( "Auto Mode Chooser", autoChooser );
	autonomousCommand = (Command *) autoChooser->GetSelected();
	printf("2135: Building autonomous chooser complete\n");
}
	
void Robot::AutonomousInit() {
	printf( "2135: Autonomous Init\n" );
	autonomousCommand = (Command *) autoChooser->GetSelected();
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
	if (autonomousCommand != NULL)
		autonomousCommand->Cancel();
}
	
void Robot::TeleopPeriodic() {
	if (autonomousCommand != NULL)
		Scheduler::GetInstance()->Run();
	SmartDashboard::PutNumber("L: Distance", Robot::chassis->leftDriveEncoder->GetDistance());
	SmartDashboard::PutNumber("R: Distance", -Robot::chassis->rightDriveEncoder->GetDistance());
	SmartDashboard::PutBoolean("Shooter Energized 1", Robot::shooter->retractLimit1->Get());
	SmartDashboard::PutBoolean("Shooter Energized 2", Robot::shooter->retractLimit2->Get());
	SmartDashboard::PutNumber("L: Speed", Robot::chassis->GetLeftSpeed());
	SmartDashboard::PutNumber("R: Speed", Robot::chassis->GetRightSpeed());
}
void Robot::DisabledInit() {
    CheesyVisionServer *cheeseView = CheesyVisionServer::GetInstance();
    cheeseView->StartSamplingCounts();
    cheeseView->StartListening();	
}
void Robot::DisabledPeriodic() {
    CheesyVisionServer *cheeseView = CheesyVisionServer::GetInstance();
    SmartDashboard::PutNumber("CheeseLeft:", cheeseView->GetLeftStatus());
    SmartDashboard::PutNumber("CheeseRight:", cheeseView->GetRightStatus());
    SmartDashboard::PutNumber("CheeseLeft Count:", cheeseView->GetLeftCount());
    SmartDashboard::PutNumber("CheeseRight Count:", cheeseView->GetRightCount());
    SmartDashboard::PutNumber("CheeseTotal Count:", cheeseView->GetTotalCount());
    SmartDashboard::PutBoolean("Cheesy Connected:", cheeseView->HasClientConnection());
	
}
void Robot::TestPeriodic() {
	lw->Run();
}
START_ROBOT_CLASS(Robot);
