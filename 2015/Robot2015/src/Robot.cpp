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
#include "Commands/AutoCommand.h"
#include "Commands/AutoContainerSet.h"
#include "Commands/AutoStackTote.h"
#include "Commands/AutoToteSet.h"
#include "Commands/DriveStop.h"
#include "Commands/DriveDistance.h"
#include "Commands/DriveDistanceTimed.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
Chassis* Robot::chassis = 0;
HWheel* Robot::hWheel = 0;
Intake* Robot::intake = 0;
Stacker* Robot::stacker = 0;
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
	hWheel = new HWheel();
	intake = new Intake();
	stacker = new Stacker();
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
	// instantiate the command used for the autonomous period
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	autonomousCommand = new AutoCommand();

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS

	printf("2135: RobotInit initialize from preferences file\n");
	prefs = Preferences::GetInstance();
	if (prefs->ContainsKey("AutoDriveDistance")) {
		m_autoSetpoint = prefs->GetDouble("AutoDriveDistance", 95.0);
		printf("2135: AutoDriveDistance Found\n");
	} else {
		printf("2135: ERROR - AutoDriveDistance Not Found\n");
	}
	if (prefs->ContainsKey("PidMinOutput")) {
		m_drivePidMin = prefs->GetDouble("DrivePidMin", -0.6);
		printf("2135: DrivePidMin Found\n");
	} else {
		printf("2135: ERROR - DrivePidMin Not Found\n");
	}
	if (prefs->ContainsKey("PidMaxOutput")) {
		m_drivePidMax = prefs->GetDouble("DrivePidMax", 0.6);
		printf("2135: DrivePidMax Found\n");
	} else {
		printf("2135: ERROR - DrivePidMax Not Found\n");
	}
	if (prefs->ContainsKey("SpinTurnSpeed")) {
		m_spinTurnSpeed = prefs->GetDouble("SpinTurnSpeed", 0.5);
		printf("2135: SpinTurnSpeed Found\n");
	} else {
		printf("2135: ERROR - SpinTurnSpeed Not Found\n");
	}
	if (prefs->ContainsKey("ElevatorSpeed")) {
		m_elevatorSpeed = prefs->GetDouble("ElevatorSpeed", 0.5);
		printf("2135: ElevatorSpeed Found\n");
	} else {
		printf("2135: ERROR - ElevatorSpeed Not Found\n");
	}
	if (prefs->ContainsKey("ElevatorPidMin")) {
		m_elevatorPidMin = prefs->GetDouble("ElevatorPidMin", 0.1);
		printf("2135: ElevatorPidMin Found\n");
	} else {
		printf("2135: ERROR - ElevatorPidMin Not Found\n");
	}
	if (prefs->ContainsKey("ElevatorPidMax")) {
		m_elevatorPidMax = prefs->GetDouble("ElevatorPidMax", 0.9);
		printf("2135: ElevatorPidMax Found\n");
	} else {
		printf("2135: ERROR - ElevatorPidMax Not Found\n");
	}
	if (prefs->ContainsKey("ChassisMinRange")) {
		m_chassisMinRange = prefs->GetDouble("ChassisMinRange", 48.0);
		printf("2135: ChassisMinRange Found\n");
	} else {
		printf("2135: ERROR - ChassisMinRange Not Found\n");
	}
	if (prefs->ContainsKey("ChassisMaxRange")) {
		m_chassisMaxRange = prefs->GetDouble("ChassisMaxRange", 54.0);
		printf("2135: ChassisMaxRange Found\n");
	} else {
		printf("2135: ERROR - ChassisMaxRange Not Found\n");
	}

	printf("AutoDriveDistance: %f\n", m_autoSetpoint);
	printf("DrivePidMax:       %f\n", m_drivePidMax);
	printf("DrivePidMin:       %f\n", m_drivePidMin);
	printf("SpinTurnSpeed:     %f\n", m_spinTurnSpeed);
	printf("ElevatorSpeed:     %f\n", m_elevatorSpeed);
	printf("ElevatorPidMin:    %f\n", m_elevatorPidMin);
	printf("ElevatorPidMax:    %f\n", m_elevatorPidMax);
	printf("ChassisMinRange:   %f\n", m_chassisMinRange);
	printf("ChassisMaxRange:   %f\n", m_chassisMaxRange);

	printf("2135: RobotInit build autonomous chooser\n");
	autoChooser = new SendableChooser();
	autoChooser->AddDefault("0 - Move forward", new DriveDistance());
	autoChooser->AddObject("1 - Sit still", new DriveStop());
	autoChooser->AddObject("2 - Container set", new AutoContainerSet());
	autoChooser->AddObject("3 - Stack tote", new AutoStackTote());
	autoChooser->AddObject("4 - Tote set", new AutoToteSet());
	autoChooser->AddObject("5 - Move forward timed", new DriveDistanceTimed());
	SmartDashboard::PutData("Auto modes", autoChooser);
	//autoChooser->AddObject("Score one tote", new );

	Robot::InitSmartDashboard();
}

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

void Robot::InitSmartDashboard() {

	printf("2135: Init SmartDashboard\n");

	SmartDashboard::PutNumber("L: P", chassis->leftPID->GetP());
	SmartDashboard::PutNumber("L: I", chassis->leftPID->GetI());
	SmartDashboard::PutNumber("L: D", chassis->leftPID->GetD());
	SmartDashboard::PutNumber("L: Tolerance", 0.2);
	SmartDashboard::PutNumber("L: Min Output", m_drivePidMin);
	SmartDashboard::PutNumber("L: Max Output", m_drivePidMax);
	SmartDashboard::PutNumber("L: Distance PP", 4 * M_PI / 360);
	SmartDashboard::PutNumber("L: Distance", chassis->encoderL->GetDistance());

	SmartDashboard::PutNumber("R: P", chassis->rightPID->GetP());
	SmartDashboard::PutNumber("R: I", chassis->rightPID->GetI());
	SmartDashboard::PutNumber("R: D", chassis->rightPID->GetD());
	SmartDashboard::PutNumber("R: Tolerance", 0.2);
	SmartDashboard::PutNumber("R: Min Output", m_drivePidMin);
	SmartDashboard::PutNumber("R: Max Output", m_drivePidMax);
	SmartDashboard::PutNumber("R: Distance PP", 4 * M_PI / 360);
	SmartDashboard::PutNumber("R: Distance", chassis->encoderR->GetDistance());

	SmartDashboard::PutBoolean("Pressure Switch Value", false);
	SmartDashboard::PutNumber("Compressor Current", 0.0);
	SmartDashboard::PutNumber("Target Setpoint", m_autoSetpoint);
	SmartDashboard::PutNumber("Left Setpoint", 0.0);
	SmartDashboard::PutNumber("Right Setpoint", 0.0);
	SmartDashboard::PutBoolean("Left PID State", false);
	SmartDashboard::PutBoolean("Right PID State", false);
	SmartDashboard::PutNumber("Temperature",
			Robot::pneumatics->CheckTemperature());
	SmartDashboard::PutNumber("Potentiometer",
			Robot::elevator->heightPot->Get());
	SmartDashboard::PutBoolean("ToteFullIn", Robot::stacker->toteFullIn->Get());
	SmartDashboard::PutBoolean("ToteFullOut",
			Robot::stacker->toteFullOut->Get());
	SmartDashboard::PutBoolean("UpperLimit", Robot::elevator->upperLimit->Get());
	SmartDashboard::PutBoolean("LowerLimit", Robot::elevator->lowerLimit->Get());
}

void Robot::UpdateSmartDashboard() {
	static int counter = 0;
	if (counter++ < 20) {
		return;
	}
	else {
		SmartDashboard::PutNumber("L: Distance",
				Robot::chassis->encoderL->GetDistance());
		SmartDashboard::PutNumber("L: Speed", Robot::chassis->DriveGetLeftSpeed());
		SmartDashboard::PutNumber("L: Avg Speed",
				Robot::chassis->DriveGetLeftSpeedAverage());

		SmartDashboard::PutNumber("R: Distance",
				Robot::chassis->encoderR->GetDistance());
		SmartDashboard::PutNumber("R: Speed",
				-Robot::chassis->DriveGetRightSpeed());
		SmartDashboard::PutNumber("R: Avg Speed",
				Robot::chassis->DriveGetRightSpeedAverage());

//	SmartDashboard::PutBoolean("Pressure Switch Value", Robot::pneumatics->compressor->GetPressureSwitchValue());
//	SmartDashboard::PutNumber("Compressor Current", Robot::pneumatics->compressor->GetCompressorCurrent());
		SmartDashboard::PutNumber("Temperature", Robot::pneumatics->CheckTemperature());
		SmartDashboard::PutNumber("Potentiometer", Robot::elevator->heightPot->Get());
		SmartDashboard::PutBoolean("ToteFullIn", Robot::stacker->toteFullIn->Get());
		SmartDashboard::PutBoolean("ToteFullOut",
				Robot::stacker->toteFullOut->Get());
		SmartDashboard::PutBoolean("UpperLimit", Robot::elevator->upperLimit->Get());
		SmartDashboard::PutBoolean("LowerLimit", Robot::elevator->lowerLimit->Get());
		counter = 0;
	}
}

START_ROBOT_CLASS(Robot);

