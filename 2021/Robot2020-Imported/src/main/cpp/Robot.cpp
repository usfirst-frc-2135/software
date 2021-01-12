// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include <Robot.h>

#include <hal/FRCUsageReporting.h>

#include <frc/commands/Scheduler.h>
#include <frc/RobotController.h>
#include <frc/Filesystem.h>
#include <wpi/Path.h>
#include <wpi/SmallString.h>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
std::shared_ptr<Drivetrain> Robot::drivetrain;
std::shared_ptr<Intake> Robot::intake;
std::shared_ptr<Conveyor> Robot::conveyor;
std::shared_ptr<Shooter> Robot::shooter;
std::shared_ptr<Spinner> Robot::spinner;
std::shared_ptr<Climber> Robot::climber;
std::shared_ptr<Power> Robot::power;
std::shared_ptr<Pneumatics> Robot::pneumatics;
std::shared_ptr<Vision> Robot::vision;
std::shared_ptr<Led> Robot::led;
std::unique_ptr<OI> Robot::oi;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION

frc::SendableChooser<std::string> *Robot::pathChooser = nullptr;

void Robot::RobotInit()
{
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
drivetrain.reset(new Drivetrain());
intake.reset(new Intake());
conveyor.reset(new Conveyor());
shooter.reset(new Shooter());
spinner.reset(new Spinner());
climber.reset(new Climber());
power.reset(new Power());
pneumatics.reset(new Pneumatics());
vision.reset(new Vision());
led.reset(new Led());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS

    // This MUST be here. If the OI creates Commands (which it very likely
    // will), constructing it during the construction of CommandBase (from
    // which commands extend), subsystems are not guaranteed to be
    // yet. Thus, their requires() statements may grab null pointers. Bad
    // news. Don't move it.
    oi.reset(new OI());

    HAL_Report(HALUsageReporting::kResourceType_Framework,
        HALUsageReporting::kFramework_RobotBuilder);

    // Add commands to Autonomous Sendable Chooser

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS

	chooser.AddOption("Auto Stop", new AutoStop());
	chooser.AddOption("Auto Drive Dist: DEFAULT", new AutoDriveDist(0));
	chooser.AddOption("Auto Shoot Drive", new AutoShootDrive());

	chooser.SetDefaultOption("Auto Stop", new AutoStop());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS

    frc::SmartDashboard::PutData("Auto Modes", &chooser);
    // TODO: Why do we need to call Initialize here? Can this be absorbed in the contructor?
    led->Initialize();

    SmartDashboardStartChooser();

    wpi::SmallString<64> deployDirectory;
    frc::filesystem::GetDeployDirectory(deployDirectory);
    wpi::sys::path::append(deployDirectory, "output");
    wpi::sys::path::append(deployDirectory, pathChooser->GetSelected());
    wpi::sys::path::append(deployDirectory, "testingpath3-curve.wpilib.json");

    std::printf("Chooser path: %s\n", deployDirectory.c_str());
}

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit()
{

}

void Robot::DisabledPeriodic()
{
    frc::Scheduler::GetInstance()->Run();

    // If RoboRIO User button is pressed, dump all CAN faults
    if (frc::RobotController::GetUserButton())
    {
        if (!m_faultsCleared)
        {
            m_faultsCleared = true;
            RobotFaultDump();
        }
    }
    else if (m_faultsCleared)
    {
        m_faultsCleared = false;
    }
}

void Robot::AutonomousInit()
{
    autonomousCommand = chooser.GetSelected();
    if (autonomousCommand != nullptr)
        autonomousCommand->Start();
}

void Robot::AutonomousPeriodic()
{
    frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit()
{
    // This makes sure that the autonomous stops running when
    // teleop starts running. If you want the autonomous to
    // continue until interrupted by another command, remove
    // these lines or comment it out.
    if (autonomousCommand != nullptr)
        autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic()
{
    frc::Scheduler::GetInstance()->Run();
}

void Robot::RobotPeriodic()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////
//  Set up Autonomous chooser

void Robot::SmartDashboardStartChooser(void)
{
  delete pathChooser;
  pathChooser = new frc::SendableChooser<std::string>;

  pathChooser->AddOption("line", "testingpath1-line.wpilib.json");
  pathChooser->AddOption("arc", "testingpath2-arc.wpilib.json");
  pathChooser->AddOption("curve", "testingpath3-curve.wpilib.json");
  pathChooser->AddOption("nose", "testingpath4-nose.wpilib.json");
  pathChooser->AddOption("scur", "testingpath5-scur.wpilib.json");

  frc::SmartDashboard::PutData("output", pathChooser);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//  Fault handling utilities

void Robot::RobotFaultDump(void)
{
    //    Print out talon SRX faults and clear sticky ones
    std::printf("2135: %s --------------\n", "FAULT DUMPS");
    drivetrain->FaultDump();
    intake->FaultDump();
    conveyor->FaultDump();
    shooter->FaultDump();
    // climber->FaultDump();
    // spinner->FaultDump();
    pneumatics->FaultDump();
    power->FaultDump();
}

/* Robot Main */

#ifndef RUNNING_FRC_TESTS
int main(int argc, char** argv)
{
    return frc::StartRobot<Robot>();
}
#endif
