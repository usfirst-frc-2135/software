// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.
#include "Robot.h"
#include "Commands/AutoRecyclingBin.h"
#include "Commands/AutoContainerSet.h"
#include "Commands/DriveStop.h"
#include "Commands/DriveDistance.h"
#include "Commands/DriveDistanceTimed.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
Chassis* Robot::chassis = 0;
Intake* Robot::intake = 0;
Gripper* Robot::gripper = 0;
Elevator* Robot::elevator = 0;
Pneumatics* Robot::pneumatics = 0;
OI* Robot::oi = 0;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION

void Robot::RobotInit() {
	printf("2135: RobotInit startup\n");
	RobotMap::init();

	printf("2135: RobotInit instantiate subsystems\n");
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	chassis = new Chassis();
	intake = new Intake();
	gripper = new Gripper();
	elevator = new Elevator();
	pneumatics = new Pneumatics();

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS

	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	printf("2135: RobotInit instantiate OI\n");
	oi = new OI();

	printf("2135: RobotInit initialize Live Window\n");
	lw = LiveWindow::GetInstance();

	printf("2135: RobotInit initialize from preferences file\n");
	prefs = Preferences::GetInstance();
	InitFromPreferencesFile();

	// instantiate the command used for the autonomous period
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	autonomousCommand = new AutoCommand();

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS

	printf("2135: RobotInit build autonomous chooser\n");
	autoChooser = new SendableChooser();
	autoChooser->AddDefault("0 - Sit still", new DriveStop());
	autoChooser->AddObject( "1 - Move forward timed", new DriveDistanceTimed());
	autoChooser->AddObject( "2 - Move forward encoder", new DriveDistance());
	autoChooser->AddObject( "3 - Recycling Bin", new AutoRecyclingBin());
	autoChooser->AddObject( "4 - Container set", new AutoContainerSet());
	SmartDashboard::PutData("Auto modes", autoChooser);
	//autoChooser->AddObject("Score one tote", new );

	Robot::InitSmartDashboard();
}

// testing commits to github
// second test for github

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit() {
	printf("2135: Disabled Init\n");
}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
	// Workaround to access all CAN devices to ensure correct initialization
	Robot::pneumatics->EnableClosedLoopControl();
	Robot::chassis->DriveSetNeutralMode();
	Robot::elevator->SetNeutralMode();
	UpdateSmartDashboard();
}

void Robot::AutonomousInit() {
	printf("2135: Autonomous Init");
	autonomousCommand = (Command *) autoChooser->GetSelected();
	if (autonomousCommand != NULL)
		autonomousCommand->Start();
	// follower mode in AutonomousInit is a backup if setting both drive
	// motors in Chassis to 0.0 does not work
	Robot::chassis->motorL3->SetControlMode(CANSpeedController::kFollower);
	Robot::chassis->motorL3->Set(2);

	Robot::chassis->motorR5->SetControlMode(CANSpeedController::kFollower);
	Robot::chassis->motorR5->Set(4);
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
	UpdateSmartDashboard();
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to 
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	if (autonomousCommand != NULL)
		autonomousCommand->Cancel();
	// follower mode is not working when the Chassis constructor is called
	// so we are calling the follower mode in the teleop init
	Robot::chassis->motorL3->SetControlMode(CANSpeedController::kFollower);
	Robot::chassis->motorL3->Set(2);

	Robot::chassis->motorR5->SetControlMode(CANSpeedController::kFollower);
	Robot::chassis->motorR5->Set(4);
	printf("Teleop Init\n");
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
	UpdateSmartDashboard();

}

void Robot::TestPeriodic() {
	lw->Run();
}

// Our initialization methods

void Robot::InitFromPreferencesFile( void )
{
	if (prefs->ContainsKey("DriveScaleFactor")) {
		chassis->SetDriveScaleFactor( prefs->GetDouble("DriveScaleFactor", 0.71) );
		printf("2135: DriveScaleFactor Found\n");
	} else {
		printf("2135: ERROR - DriveScaleFactor Not Found\n");
	}

	if (prefs->ContainsKey("DriveDistance")) {
		chassis->SetDriveDistance( prefs->GetDouble("DriveDistance", 72.1) );
		printf("2135: DriveDistance Found\n");
	} else {
		printf("2135: ERROR - DriveDistance Not Found\n");
	}

	if (prefs->ContainsKey("DriveDistanceTimed")) {
		chassis->SetDriveDistanceTimed( prefs->GetDouble("DriveDistanceTimed", 1.25) );
		printf("2135: DriveDistanceTimed Found\n");
	} else {
		printf("2135: ERROR - DriveDistance Not Found\n");
	}

	if (prefs->ContainsKey("DrivePidSpeedMin")) {
		chassis-> SetDrivePidSpeedMin( prefs->GetDouble("DrivePidSpeedMin", -0.51) );
		printf("2135: DrivePidSpeedMin Found\n");
	} else {
		printf("2135: ERROR - DrivePidSpeedMin Not Found\n");
	}

	if (prefs->ContainsKey("DrivePidSpeedMax")) {
		chassis-> SetDrivePidSpeedMax ( prefs->GetDouble("DrivePidSpeedMax", 0.51) );
		printf("2135: DrivePidSpeedMax Found\n");
	} else {
		printf("2135: ERROR - DrivePidSpeedMax Not Found\n");
	}

	if (prefs->ContainsKey("DriveSpinSpeed")) {
		chassis->SetDriveSpinTurnSpeed ( prefs->GetDouble("DriveSpinSpeed", 0.31) );
		printf("2135: DriveSpinSpeed Found\n");
	} else {
		printf("2135: ERROR - SpinTurnSpeed Not Found\n");
	}

	if (prefs->ContainsKey("ElevatorSpeed")) {
		elevator-> SetElevatorSpeed ( prefs->GetDouble("ElevatorSpeed", 0.51) );
		printf("2135: ElevatorSpeed Found\n");
	} else {
		printf("2135: ERROR - ElevatorSpeed Not Found\n");
	}

	if (prefs->ContainsKey("ElevatorPidMin")) {
		elevator-> SetElevatorPidMin ( prefs->GetDouble("ElevatorPidMin", 10.1) );
		printf("2135: ElevatorPidMin Found\n");
	} else {
		printf("2135: ERROR - ElevatorPidMin Not Found\n");
	}

	if (prefs->ContainsKey("ElevatorPidMax")) {
		elevator-> SetElevatorPidMax( prefs->GetDouble("ElevatorPidMax", 35.1) );
		printf("2135: ElevatorPidMax Found\n");
	} else {
		printf("2135: ERROR - ElevatorPidMax Not Found\n");
	}

	if (prefs->ContainsKey("IntakeSpeed")) {
		intake-> SetIntakeSpeed( prefs->GetDouble("IntakeSpeed", 0.51) );
		printf("2135: IntakeSpeed Found\n");
	} else {
		printf("2135: ERROR - IntakeSpeed Not Found\n");
	}

	if (prefs->ContainsKey("HWheelSpeed")) {
		chassis->SetHWheelSpeed( prefs->GetDouble("HWheelSpeed", 0.31) );
		printf("2135: HWheelSpeed Found\n");
	} else {
		printf("2135: ERROR - HWheelSpeed Not Found\n");
	}
}

void Robot::InitSmartDashboard( void ) {

	printf("2135: Init SmartDashboard\n");

	SmartDashboard::PutNumber("L: Distance", chassis->encoderL->GetDistance());
	SmartDashboard::PutNumber("L: Distance PP", 4 * M_PI / 360);
	SmartDashboard::PutNumber("L: P", chassis->leftPID->GetP());
	SmartDashboard::PutNumber("L: I", chassis->leftPID->GetI());
	SmartDashboard::PutNumber("L: D", chassis->leftPID->GetD());
	SmartDashboard::PutNumber("L: Tolerance", 0.2);
	SmartDashboard::PutNumber("L: Min Output", chassis->GetDrivePidSpeedMin());
	SmartDashboard::PutNumber("L: Max Output", chassis->GetDrivePidSpeedMax());
	SmartDashboard::PutNumber("Left Setpoint", 0.0);
	SmartDashboard::PutBoolean("Left PID State", false);

	SmartDashboard::PutNumber("R: Distance", chassis->encoderR->GetDistance());
	SmartDashboard::PutNumber("R: Distance PP", 4 * M_PI / 360);
	SmartDashboard::PutNumber("R: P", chassis->rightPID->GetP());
	SmartDashboard::PutNumber("R: I", chassis->rightPID->GetI());
	SmartDashboard::PutNumber("R: D", chassis->rightPID->GetD());
	SmartDashboard::PutNumber("R: Tolerance", 0.2);
	SmartDashboard::PutNumber("R: Min Output", chassis->GetDrivePidSpeedMin());
	SmartDashboard::PutNumber("R: Max Output", chassis->GetDrivePidSpeedMax());
	SmartDashboard::PutNumber("Right Setpoint", 0.0);
	SmartDashboard::PutBoolean("Right PID State", false);

	SmartDashboard::PutNumber("Drive Distance", chassis->GetDriveDistance());

	SmartDashboard::PutNumber("Potentiometer", Robot::elevator->heightPot->Get());

	SmartDashboard::PutBoolean("UpperLimit", -Robot::elevator->upperLimit->Get());
	SmartDashboard::PutBoolean("LowerLimit", -Robot::elevator->lowerLimit->Get());

	SmartDashboard::PutBoolean("Pressure Switch Value", false);
	SmartDashboard::PutNumber("Compressor Current", 0.0);
	SmartDashboard::PutNumber("Temperature", Robot::pneumatics->CheckTemperature());
}

void Robot::UpdateSmartDashboard( void ) {
	static int counter = 0;

	// Unused readings are commented out
	switch (counter++)
	{
	case 0:
//		SmartDashboard::PutNumber("L: Distance",  Robot::chassis->encoderL->GetDistance());
//		SmartDashboard::PutNumber("R: Distance",  Robot::chassis->encoderR->GetDistance());
		SmartDashboard::PutNumber("Potentiometer", Robot::elevator->heightPot->Get());
		break;
	case 5:
//		SmartDashboard::PutNumber("L: Speed",     Robot::chassis->DriveGetLeftSpeed());
//		SmartDashboard::PutNumber("R: Speed",	 -Robot::chassis->DriveGetRightSpeed());
		SmartDashboard::PutBoolean("UpperLimit", -Robot::elevator->upperLimit->Get());
		break;
	case 10:
//		SmartDashboard::PutNumber("L: Avg Speed", Robot::chassis->DriveGetLeftSpeedAverage());
//		SmartDashboard::PutNumber("R: Avg Speed", Robot::chassis->DriveGetRightSpeedAverage());
		SmartDashboard::PutBoolean("LowerLimit", -Robot::elevator->lowerLimit->Get());
		break;
	case 15:
		// SmartDashboard::PutNumber("Throttle", fabs(Robot::oi->getJoystick1()->GetThrottle()));
		break;
	case 20:
		//	SmartDashboard::PutBoolean("Pressure Switch Value", Robot::pneumatics->compressor->GetPressureSwitchValue());
		break;
	case 25:
		//	SmartDashboard::PutNumber("Compressor Current", Robot::pneumatics->compressor->GetCompressorCurrent());
		break;
	case 30:
		// SmartDashboard::PutNumber("Temperature", Robot::pneumatics->CheckTemperature());
		break;
	default:
		break;
	}

	if (counter == 25)
		counter = 0;
}

START_ROBOT_CLASS(Robot);
