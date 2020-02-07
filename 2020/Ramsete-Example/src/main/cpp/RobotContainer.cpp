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

RobotContainer::RobotContainer() {
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();

  // Set up default drive command
  m_drive.SetDefaultCommand(frc2::RunCommand(
    [this] {
      m_drive.ArcadeDrive(
        m_driverController.GetY(frc::GenericHID::kLeftHand),
        m_driverController.GetX(frc::GenericHID::kRightHand)
        );
    },
    {&m_drive}
  ));
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here

  // While holding the shoulder button, drive at half speed
  frc2::JoystickButton(&m_driverController, 6)
      .WhenPressed(&m_driveHalfSpeed)
      .WhenReleased(&m_driveFullSpeed);
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // Create a voltage constraint to ensure we don't accelerate too fast
  frc::DifferentialDriveVoltageConstraint autoVoltageConstraint(
      frc::SimpleMotorFeedforward<units::meters>(
          DriveConstants::ks,
          DriveConstants::kv,
          DriveConstants::ka
        ),
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

  // An example trajectory to follow.  All units in meters.
  auto exampleTrajectory = frc::TrajectoryGenerator::GenerateTrajectory(
      // Start at the origin facing the +X direction
      frc::Pose2d(0_m, 0_m, frc::Rotation2d(0_deg)),
      // Pass through these two interior waypoints, making an 's' curve path
      {frc::Translation2d(.7_m, .35_m), frc::Translation2d(1.05_m, -.35_m)},
      // End 3 meters straight ahead of where we started, facing forward
      frc::Pose2d(1.75_m, 0_m, frc::Rotation2d(0_deg)),
      // Pass the config
      config
    );

   wpi::SmallString<64> deployDirectory;
   frc::filesystem::GetDeployDirectory(deployDirectory);
   wpi::sys::path::append(deployDirectory, "paths");
   wpi::sys::path::append(deployDirectory, "Blue Alliance Team 1.wpilib.json");
   wpi::sys::path::append(deployDirectory, "Blue Alliance Team 2.wpilib.json");
   wpi::sys::path::append(deployDirectory, "Blue Alliance Team 3.wpilib.json");
   wpi::sys::path::append(deployDirectory, "Red Alliance Team 1.wpilib.json");
   wpi::sys::path::append(deployDirectory, "Red Alliance Team 2.wpilib.json");
   wpi::sys::path::append(deployDirectory, "Red Alliance Team 3.wpilib.json");
   wpi::sys::path::append(deployDirectory, "Test 'Square'.wpilib.json");
   wpi::sys::path::append(deployDirectory, "Test Path 1.wpilib.json");
   wpi::sys::path::append(deployDirectory, "Test Path 3.wpilib.json");
   wpi::sys::path::append(deployDirectory, "Test Path 4.wpilib.json");

   frc::Trajectory trajectory = frc::TrajectoryUtil::FromPathweaverJson(deployDirectory);

  frc2::PIDController leftController(DriveConstants::kPDriveVel, 0,0);
  frc2::PIDController rightController(DriveConstants::kPDriveVel, 0,0);

  double dashValue;
  dashValue = frc::SmartDashboard::GetNumber("L_Ctr", 0.99);

  leftController.SetTolerance(dashValue);
  rightController.SetTolerance(dashValue);

  frc2::RamseteCommand ramseteCommand(
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
  return new frc2::SequentialCommandGroup(
      std::move(ramseteCommand),
      frc2::InstantCommand([this] { m_drive.TankDriveVolts(0_V, 0_V); },
      {})
    );

 
}
