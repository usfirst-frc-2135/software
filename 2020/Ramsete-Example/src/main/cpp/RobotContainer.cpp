/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"

#include <frc/controller/PIDController.h>
#include <frc/controller/RamseteController.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/trajectory/Trajectory.h>
#include <frc/trajectory/TrajectoryGenerator.h>
#include <frc/trajectory/constraint/DifferentialDriveVoltageConstraint.h>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/RamseteCommand.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/button/JoystickButton.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include <frc/Filesystem.h>
#include <frc/trajectory/TrajectoryUtil.h>
#include <wpi/Path.h>
#include <wpi/SmallString.h>


#include "Constants.h"

frc::SendableChooser<std::string> *RobotContainer::chooser = nullptr;

// JLM: Since we are not using a RobotContainer model in our code right now,
// we need to port these methods into our code

RobotContainer::RobotContainer()
{
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  // JLM: We don't need to do this, because our OI.c does it
  ConfigureButtonBindings();

  // JLM: Need something like this in our RobotInit method
  SmartDashboardStartChooser();

  // Set up default drive command
  // JLM: We don't need to do this, because it is in our Drivetrain.c
  m_drive.SetDefaultCommand(frc2::RunCommand(
    [this] {
      m_drive.ArcadeDrive(m_driverController.GetY(frc::GenericHID::kLeftHand), m_driverController.GetX(frc::GenericHID::kRightHand));
    },
    {&m_drive}
  ));
}

// JLM: This is done already in our OI files
void RobotContainer::ConfigureButtonBindings()
{
  // Configure your button bindings here

  // While holding the shoulder button, drive at half speed
  frc2::JoystickButton(&m_driverController, 6)
    .WhenPressed(&m_driveHalfSpeed)
    .WhenReleased(&m_driveFullSpeed);
}

// JLM: This whole method needs to be ported into Drivetrain file so we can use it
// Try it as is and see how far we can get

frc2::Command* RobotContainer::GetAutonomousCommand()
{
  // Create a voltage constraint to ensure we don't accelerate too fast
  // JLM: This looks like a bug because we are applying <units::meters> to
  // parameter that should be a voltage
  // Since this is all dealing with Drivetrain stuff, it should make sense

  frc::DifferentialDriveVoltageConstraint autoVoltageConstraint
  (
    frc::SimpleMotorFeedforward<units::meters>(DriveConstants::ks,
    DriveConstants::kv,
    DriveConstants::ka),
    DriveConstants::kDriveKinematics,
    10_V
  );

  // Set up config for trajectory
  frc::TrajectoryConfig config(AutoConstants::kMaxSpeed, AutoConstants::kMaxAcceleration);

  // Add kinematics to ensure max speed is actually obeyed
  config.SetKinematics(DriveConstants::kDriveKinematics);

  // Apply the voltage constraint
  config.AddConstraint(autoVoltageConstraint);

  m_drive.ResetOdometry(frc::Pose2d());

  // An example trajectory to follow.  All units in feet.
#if 0
  frc::Trajectory exampleTrajectory = frc::TrajectoryGenerator::GenerateTrajectory(
      // Start at the origin facing the +X direction
      frc::Pose2d(0_ft, 0_ft, frc::Rotation2d(0_deg)),
      // Pass through these two interior waypoints, making an 's' curve path
      { frc::Translation2d(0.8_ft, 0.8_ft), frc::Translation2d(1.6_ft, -0.8_ft) },
      // End 3 feet straight ahead of where we started, facing forward
      frc::Pose2d(2.4_ft, 0_ft, frc::Rotation2d(0_deg)),
      // Pass the config
      config
    );
#endif

   // TODO: Fix path does not exist error
  wpi::SmallString<64> deployDirectory;
  frc::filesystem::GetDeployDirectory(deployDirectory);
  wpi::sys::path::append(deployDirectory, "output");
  wpi::sys::path::append(deployDirectory, chooser->GetSelected());
  wpi::sys::path::append(deployDirectory, "testingpath3-curve.wpilib.json");

  std::string path = chooser->GetSelected();

  std::printf("%s\n", path.c_str());

  frc::Trajectory trajectory;
  std::vector<frc::Trajectory::State> trajectoryStates;

  trajectory = frc::TrajectoryUtil::FromPathweaverJson(deployDirectory);
  trajectoryStates = trajectory.States();

  printf("Size of state table is %d\n", trajectoryStates.size());

  for (uint i = 0; i < trajectoryStates.size(); i++)
  {
    frc::Trajectory::State curState = trajectoryStates[i];
    std::cout
      << "state time: " << curState.t
      << ", Velocity: " << curState.velocity
      << ", Acceleration: " <<  curState.acceleration
      << ", Rotation: " << curState.pose.Rotation().Degrees()
      << "\n";
  }

  frc2::PIDController leftController(DriveConstants::kPDriveVel, 0,0);
  frc2::PIDController rightController(DriveConstants::kPDriveVel, 0,0);

  double dashValue;
  dashValue = frc::SmartDashboard::GetNumber("L_Ctr", 0.99);

  leftController.SetTolerance(dashValue);
  rightController.SetTolerance(dashValue);

  frc2::RamseteCommand ramseteCommand
  (
    trajectory,
    [this]() { return m_drive.GetPose(); },
    frc::RamseteController(AutoConstants::kRamseteB, AutoConstants::kRamseteZeta),
    frc::SimpleMotorFeedforward<units::meters>(DriveConstants::ks, DriveConstants::kv, DriveConstants::ka),
    DriveConstants::kDriveKinematics,
    [this] { return m_drive.GetWheelSpeeds(); },
    leftController,
    rightController,
    [this](auto left, auto right) { m_drive.TankDriveVolts(left, right); },
    {&m_drive}
  );

  // no auto
  // JLM: This is not how we launch our autonomous commands, but we can modify it
  // after it's ported in (or decide to just use it)
  return new frc2::SequentialCommandGroup
  (
    std::move(ramseteCommand),
    frc2::InstantCommand
    (
      [this] { m_drive.TankDriveVolts(0_V, 0_V); },
      {}
    )
  );
}

// JLM: This is the function that should be called in RobotInit
// It should be ported into Robot.c (near bottom of file)
void RobotContainer::SmartDashboardStartChooser()
{
  delete chooser;
  chooser = new frc::SendableChooser<std::string>;

  chooser->AddOption("line", "testingpath1-line.wpilib.json");
  chooser->AddOption("arc", "testingpath2-arc.wpilib.json");
  chooser->AddOption("curve", "testingpath3-curve.wpilib.json");
  chooser->AddOption("nose", "testingpath4-nose.wpilib.json");
  chooser->AddOption("scur", "testingpath5-scur.wpilib.json");

  frc::SmartDashboard::PutData("output", chooser);
}
