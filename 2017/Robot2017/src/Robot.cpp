// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include <src/VisionLoop.h>
#include "Robot.h"
#include "Commands/AutonDefault.h"
#include "Commands/AutonPos123Move.h"
#include "Commands/AutonPos1DeliverGear.h"
#include "Commands/AutonPos2DeliverGear.h"
#include "Commands/AutonPos3DeliverGear.h"


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
std::shared_ptr<Chassis> Robot::chassis;
std::shared_ptr<Intake> Robot::intake;
std::shared_ptr<Agitator> Robot::agitator;
std::shared_ptr<Shooter> Robot::shooter;
std::shared_ptr<Delivery> Robot::delivery;
std::shared_ptr<Climber> Robot::climber;
std::shared_ptr<Pneumatics> Robot::pneumatics;
std::shared_ptr<Power> Robot::power;
std::unique_ptr<OI> Robot::oi;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION

void Robot::RobotInit() {
	RobotMap::init();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    chassis.reset(new Chassis());
    intake.reset(new Intake());
    agitator.reset(new Agitator());
    shooter.reset(new Shooter());
    delivery.reset(new Delivery());
    climber.reset(new Climber());
    pneumatics.reset(new Pneumatics());
    power.reset(new Power());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi.reset(new OI());

	// instantiate the command used for the autonomous period
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS

	SmartDashboard::PutBoolean(CAM_FOUNDTARGET, false);

	m_faultsCleared = false;
	m_dashboardUpdate = 0;

	prefs = frc::Preferences::GetInstance();

//	printf("2135: Main Thread ID %d\n", RobotBase::GetThreadId());

	std::thread m_vThread(VisionThread);
	m_vThread.detach();

	printf("2135: RobotInit - Finished\n");
}

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit(){
	m_faultsCleared = false;

	chooser.AddDefault("Auton Default", new AutonDefault());
	chooser.AddObject("Pos 123 Move", new AutonPos123Move());
	chooser.AddObject("Pos 1 Gear", new AutonPos1DeliverGear());
	chooser.AddObject("Pos 2 Gear", new AutonPos2DeliverGear());
	chooser.AddObject("Pos 3 Gear", new AutonPos3DeliverGear());
	frc::SmartDashboard::PutData("Auto Modes", &chooser);
}

void Robot::DisabledPeriodic() {
	static int ticks_per_print = 0;
	Scheduler::GetInstance()->Run();

	if (ticks_per_print++ > 100) {
//		printf("2135: DisabledPeriodic\n");
		ticks_per_print = 0;
	}

	// If RoboRIO User button is pressed, dump faults
	if (GetUserButton() && !m_faultsCleared) {
		m_faultsCleared = true;
		HandleFaults();
	}
	//	Print dashboard values only occassionally to reduce resource requirements
	if (m_dashboardUpdate++ > smartdashboardUpdateDisabled)
	{
		m_dashboardUpdate = 0;
		Robot::chassis->UpdateSmartDashboardValues();
	}
}

void Robot::AutonomousInit() {
	prefs = frc::Preferences::GetInstance();

	// Initialize SmartDashboard preferences
	chassis->Initialize(prefs);
	agitator->Initialize(prefs);
	climber->Initialize(prefs);
	delivery->Initialize(prefs);
	intake->Initialize(prefs);
	pneumatics->Initialize(prefs);
	shooter->Initialize(prefs);

	autonomousCommand.reset(chooser.GetSelected());
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();

	//	Print dashboard values only occasionally to reduce resource requirements
	if (m_dashboardUpdate++ > smartdashboardUpdateAutonomous)
	{
		m_dashboardUpdate = 0;
		Robot::chassis->UpdateSmartDashboardValues();
	}
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Cancel();

	prefs = frc::Preferences::GetInstance();

	// Initialize SmartDashboard and Subsystems
	chassis->Initialize(prefs);
	agitator->Initialize(prefs);
	climber->Initialize(prefs);
	delivery->Initialize(prefs);
	intake->Initialize(prefs);
	pneumatics->Initialize(prefs);
	shooter->Initialize(prefs);
	fflush(stdout);
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();

	//	Print dashboard values only occasionally to reduce resource requirements
	if (m_dashboardUpdate++ > smartdashboardUpdateTeleop)
	{
		m_dashboardUpdate = 0;
		Robot::chassis->UpdateSmartDashboardValues();
	}
}

void Robot::TestPeriodic() {
	lw->Run();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

//	Preference handling utilities

double Robot::LoadPreferencesVariable(std::string name, double defaultValue) {
	double value;
	Preferences *prefs;

	prefs = frc::Preferences::GetInstance();

	if (prefs->ContainsKey(name)) {
		value = prefs->GetDouble(name, defaultValue);
		printf("2135: PREF    %-30s : %6.3f\n", name.c_str(), value);
	}
	else {
		value = defaultValue;
		printf("2135: ERROR - %-30s not found\n", name.c_str());
	}

	return value;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

//	Fault handling utilities

void Robot::HandleFaults(void) {
	printf("2135: %s --------------\n", "TALON SRX FAULTS");
	TalonSRXPrintFaults("chassisMotorL1", RobotMap::chassisMotorL1);
	TalonSRXPrintFaults("chassisMotorL2", RobotMap::chassisMotorL2);
	TalonSRXPrintFaults("chassisMotorR3", RobotMap::chassisMotorR3);
	TalonSRXPrintFaults("chassisMotorR4", RobotMap::chassisMotorR4);
	TalonSRXPrintFaults("intakeMotor8", RobotMap::intakeMotor8);
	TalonSRXPrintFaults("intakeMotor9", RobotMap::intakeMotor9);
	TalonSRXPrintFaults("agitatorMotor12", RobotMap::agitatorMotor12);
	TalonSRXPrintFaults("shooterMotor14", RobotMap::shooterMotor14);
	TalonSRXPrintFaults("climberMotor18", RobotMap::climberMotor18);
	TalonSRXPrintFaults("climberMotor19", RobotMap::climberMotor19);

	printf("2135: %s --------------\n", "PCM FAULTS");
	if (RobotMap::pneumaticsCompressor->GetCompressorCurrentTooHighStickyFault())
		printf("\tCurrentTooHighFault\n");
	if (RobotMap::pneumaticsCompressor->GetCompressorNotConnectedFault())
		printf("\tCompressorNotConnectedFault\n");
	if (RobotMap::pneumaticsCompressor->GetCompressorShortedFault())
		printf("\tCompressorShortedFault\n");
	RobotMap::pneumaticsCompressor->ClearAllPCMStickyFaults();

	printf("2135: %s --------------\n", "PDP FAULTS");
	RobotMap::powerPDP->ClearStickyFaults();

	//faults
}

void Robot::TalonSRXPrintFaults(const char *talonName, std::shared_ptr<CANTalon> talonPtr) {

	uint16_t	faults;
	uint16_t	stickyFaults;

	faults = talonPtr->GetFaults();
	stickyFaults = talonPtr->GetStickyFaults();
	talonPtr->ClearStickyFaults();

	printf("2135: %s --------------\n", talonName);

	if (faults & CANTalon::kTemperatureFault)
		printf("\tkTemperatureFault\n");
	if (faults & CANTalon::kBusVoltageFault)
		printf("\tkBusVoltageFault\n");
	if (faults & CANTalon::kFwdLimitSwitch)
		printf("\tkFwdLimitSwitch\n");
	if (faults & CANTalon::kRevLimitSwitch)
		printf("\tkRevLimitSwitch\n");
	if (faults & CANTalon::kFwdSoftLimit)
		printf("\tkFwdLimitSwitch\n");
	if (faults & CANTalon::kRevSoftLimit)
		printf("\tkRevLimitSwitch\n");

	if (stickyFaults & CANTalon::kTemperatureFault)
		printf("\tSticky - kTemperatureFault\n");
	if (stickyFaults & CANTalon::kBusVoltageFault)
		printf("\tSticky - kBusVoltageFault\n");
	if (stickyFaults & CANTalon::kFwdLimitSwitch)
		printf("\tSticky - kFwdLimitSwitch\n");
	if (stickyFaults & CANTalon::kRevLimitSwitch)
		printf("\tSticky - kRevLimitSwitch\n");
	if (stickyFaults & CANTalon::kFwdSoftLimit)
		printf("\tSticky - kFwdLimitSwitch\n");
	if (stickyFaults & CANTalon::kRevSoftLimit)
		printf("\tSticky - kRevLimitSwitch\n");
}

// Vision Thread to call into our Vision processing loop

static void VisionThread() {
	// Thread checking
	printf("2135: ----- VISION THREAD RUNNING -----\n");
//	printf("2135: Vision Thread ID %d\n", std::this_thread::get_id());
	if (std::this_thread::get_id() == RobotBase::GetThreadId()) {
		printf("2135: ERROR: Vision Loop cannot be called from the main robot thread\n");
		return;
	}

	try {
		// Instantiate the vision loop and call it
		VisionLoop *vision = new VisionLoop;
		vision->Run();

		// Should never get here - if it does then clean up
		delete vision;
	}
	catch (...) {	// Error detected, loop in a sleep mode (return seems to reboot robot)
		while(1) {
			printf("2135: Vision Thread terminated due to exception\n");
			std::this_thread::sleep_for(std::chrono::seconds(10));
		}
	}
}

START_ROBOT_CLASS(Robot);
