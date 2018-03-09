// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


//#include <Commands/AutoDriveDist.h>
#include "Robot.h"

#include "FRC2135/RobotConfig.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
std::shared_ptr<Drivetrain> Robot::drivetrain;
std::shared_ptr<Elevator> Robot::elevator;
std::shared_ptr<Gripper> Robot::gripper;
std::shared_ptr<Wrist> Robot::wrist;
std::shared_ptr<Pneumatics> Robot::pneumatics;
std::unique_ptr<OI> Robot::oi;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION

void Robot::RobotInit() {
	RobotMap::init();
	std::printf("2135: RobotInit\n");

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    drivetrain.reset(new Drivetrain());
    elevator.reset(new Elevator());
    gripper.reset(new Gripper());
    wrist.reset(new Wrist());
    pneumatics.reset(new Pneumatics());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi.reset(new OI());

	// Add commands to Autonomous Sendable Chooser

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS

#ifndef ROBOTBENCHTOPTEST
	// Camera - Logitech C920
//	cs::UsbCamera LogitechCamera = CameraServer::GetInstance()->StartAutomaticCapture();
//	LogitechCamera.SetVideoMode(cs::VideoMode::kMJPEG, 640, 360, 30);

	// Camera - Microsoft LifeCam
	cs::UsbCamera MicrosoftCamera = CameraServer::GetInstance()->StartAutomaticCapture();
	MicrosoftCamera.SetVideoMode(cs::VideoMode::kMJPEG, 640, 360, 15);
#endif
	SmartDashboardStartChooser();
}

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit(){

}

void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();

	// If RoboRIO User button is pressed, dump all CAN faults
	if (RobotController::GetUserButton() && !m_faultsCleared) {
		m_faultsCleared = true;
		RobotFaultDump();
	}
}

void Robot::AutonomousInit() {
	drivetrain->MoveSetBrakeMode(true);
	drivetrain->MoveShiftGears(true);

	// Initializes the gameData that read switch and scale colors from the FMS
	std::string gameData;
	gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();

	// Reads switch closest to Alliance Station
	m_FMSAllianceSwitch = gameData[0];
	std::printf("2135: Auto Level 1 Alliance Switch %s Side\n", (m_FMSAllianceSwitch == 'L') ? "LEFT" : "RIGHT");

	// Reads scale
	m_FMSScale = gameData[1];
	std::printf("2135: Auto Level 2 Scale %s Side\n", (m_FMSScale == 'L') ? "LEFT" : "RIGHT");

	// Reads switch farthest from the Alliance Station
	m_FMSOpponentSwitch = gameData[2];
	std::printf("2135: Auto Level 3 Opponent Switch %s Side \n", (m_FMSOpponentSwitch == 'L') ? "LEFT" : "RIGHT");

	autonomousCommand = chooser.GetSelected();
	if (autonomousCommand != nullptr)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	drivetrain->MoveSetBrakeMode(false);
	drivetrain->MoveShiftGears(true);

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

bool Robot::FMSAllianceSwitchIsLeft(void) {
	return (m_FMSAllianceSwitch == 'L');
}

bool Robot::FMSScaleIsLeft(void) {
	return (m_FMSScale == 'L');
}

bool Robot::FMSOpponentSwitchIsLeft(void) {
	return (m_FMSOpponentSwitch == 'L');
}
///////////////////////////////////////////////////////////////////////////////////////////////////

//	Fault handling utilities

void Robot::RobotFaultDump(void) {
	std::printf("2135: %s --------------\n", "TALON SRX FAULTS");
	RobotFaultDumpTalonSRX("drivetrainMotorL1", RobotMap::drivetrainMotorL1);
	RobotFaultDumpTalonSRX("drivetrainMotorL2", RobotMap::drivetrainMotorL2);
	RobotFaultDumpTalonSRX("drivetrainMotorR3", RobotMap::drivetrainMotorR3);
	RobotFaultDumpTalonSRX("drivetrainMotorR4", RobotMap::drivetrainMotorR4);
	RobotFaultDumpTalonSRX("elevatorMotorL7", RobotMap::elevatorMotorL7);
	RobotFaultDumpTalonSRX("elevatorMotorR8", RobotMap::elevatorMotorR8);
	RobotFaultDumpTalonSRX("gripperMotorL11", RobotMap::gripperMotorL11);
	RobotFaultDumpTalonSRX("gripperMotorR12", RobotMap::gripperMotorR12);
	RobotFaultDumpTalonSRX("wristMotorW14", RobotMap::wristMotorW14);

	std::printf("2135: %s --------------\n", "PCM FAULTS");
	if (RobotMap::pneumaticsCompressor->GetCompressorCurrentTooHighStickyFault())
		std::printf("\tCurrentTooHighFault\n");
	if (RobotMap::pneumaticsCompressor->GetCompressorNotConnectedFault())
		std::printf("\tCompressorNotConnectedFault\n");
	if (RobotMap::pneumaticsCompressor->GetCompressorShortedFault())
		std::printf("\tCompressorShortedFault\n");
	RobotMap::pneumaticsCompressor->ClearAllPCMStickyFaults();

	std::printf("2135: %s --------------\n", "PDP FAULTS");
	// TODO: Check and fix faults
//	RobotMap::powerPDP->ClearStickyFaults();
}

void Robot::RobotFaultDumpTalonSRX(const char *talonName, std::shared_ptr<WPI_TalonSRX> talonPtr) {

	Faults			faults;
	StickyFaults	stickyFaults;

	talonPtr->GetFaults(faults);
	talonPtr->GetStickyFaults(stickyFaults);
	talonPtr->ClearStickyFaults(100);

	std::printf("2135: %s --------------\n", talonName);

	if (faults.HasAnyFault())
		std::printf("At Least one fault below\n");
	if (faults.ForwardLimitSwitch)
		std::printf("\tForwardLimitSwitch\n");
	if (faults.ForwardSoftLimit)
		std::printf("\tForwardSoftLimit\n");
	if (faults.HardwareESDReset)
		std::printf("\tHardwareESDReset\n");
	if (faults.HardwareFailure)
		std::printf("\tHardwareFailure\n");
	if (faults.RemoteLossOfSignal)
		std::printf("\tRemoteLossOfSignal\n");
	if (faults.ResetDuringEn)
		std::printf("\tResetDuringEn\n");
	if (faults.ReverseLimitSwitch)
		std::printf("\tReverseLimitSwitch\n");
	if (faults.ReverseSoftLimit)
		std::printf("\tReverseSoftLimit\n");
	if  (faults.SensorOutOfPhase)
		std::printf("\tSensorOutOfPhase\n");
	if (faults.SensorOverflow)
		std::printf("\tSensorOverflow\n");
	if (faults.UnderVoltage)
		std::printf("\tUnderVoltage\n");

	if (stickyFaults.HasAnyFault())
		std::printf("At Least one STICKY fault below\n");
	if (stickyFaults.ForwardLimitSwitch)
		std::printf("\tForwardLimitSwitch\n");
	if (stickyFaults.ForwardSoftLimit)
		std::printf("\tForwardSoftLimit\n");
	if (stickyFaults.HardwareESDReset)
		std::printf("\tHardwareESDReset\n");
//	if (stickyFaults.HardwareFailure)
//		std::printf("\tHardwareFailure\n");
	if (stickyFaults.RemoteLossOfSignal)
		std::printf("\tRemoteLossOfSignal\n");
	if (stickyFaults.ResetDuringEn)
		std::printf("\tResetDuringEn\n");
	if (stickyFaults.ReverseLimitSwitch)
		std::printf("\tReverseLimitSwitch\n");
	if (stickyFaults.ReverseSoftLimit)
		std::printf("\tReverseSoftLimit\n");
	if  (stickyFaults.SensorOutOfPhase)
		std::printf("\tSensorOutOfPhase\n");
	if (stickyFaults.SensorOverflow)
		std::printf("\tSensorOverflow\n");
	if (stickyFaults.UnderVoltage)
		std::printf("\tUnderVoltage\n");

}

void Robot::SmartDashboardStartChooser() {
	chooser.AddDefault("Auto Stop", new AutoStop());
	chooser.AddObject("Pos 123 Move", new AutoPos123Move());
	chooser.AddObject("Pos 1 Switch", new AutoPos1Switch());
	chooser.AddObject("Pos 2 Switch", new AutoPos2Switch());
	chooser.AddObject("Pos 3 Switch", new AutoPos3Switch());
	frc::SmartDashboard::PutData("Auto Modes", &chooser);
}

START_ROBOT_CLASS(Robot);

