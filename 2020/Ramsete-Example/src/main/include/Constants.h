/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/kinematics/DifferentialDriveKinematics.h>
#include <frc/trajectory/constraint/DifferentialDriveKinematicsConstraint.h>
#include <units/units.h>
#include <wpi/math>

#pragma once

/**
 * The Constants header provides a convenient place for teams to hold robot-wide
 * numerical or bool constants.  This should not be used for any other purpose.
 *
 * It is generally a good idea to place constants into subsystem- or
 * command-specific namespaces within this header, which can then be used where
 * they are needed.
 */

namespace DriveConstants
{
  // JLM: These constants may already exist or can be added to Drivetrain.h
  constexpr int kLeftMotor1Port = 1;
  constexpr int kLeftMotor2Port = 2;
  constexpr int kRightMotor1Port = 3;
  constexpr int kRightMotor2Port = 4;

  constexpr int kLeftEncoderPorts[] {1, 2};
  constexpr int kRightEncoderPorts[] {3, 4};
  constexpr bool kLeftEncoderReversed = true;
  constexpr bool kRightEncoderReversed = true;

  constexpr auto kTrackwidth = 2_ft;
  extern const frc::DifferentialDriveKinematics kDriveKinematics;

  constexpr int kEncoderCPR = 4096;
  constexpr double kWheelDiameterMeters = 0.1524;
  // Assumes the encoders are directly mounted on the wheel shafts
  constexpr double kEncoderDistancePerPulse =
      (kWheelDiameterMeters * wpi::math::pi) / static_cast<double>(kEncoderCPR);

  constexpr bool kGyroReversed = true;

  // Values for 2135 Bebula - 2019 B-bot
  // These characterization values MUST be determined either experimentally or
  // theoretically for *your* robot's drive. The Robot Characterization Toolsuite
  // provides a convenient tool for obtaining these values for your robot.
  constexpr auto ks = 0.899_V;
  constexpr auto kv = 4.63 * 1_V * 1_s / 1_ft;
  constexpr auto ka = 0.69 * 1_V * 1_s * 1_s / 1_ft;

  // As above, this must be tuned for your drive!
  constexpr double kPDriveVel = .00291;
}  // namespace DriveConstants

namespace AutoConstants
{
  // JLM: These constants may already exist or can be added to Drivetrain.h
  constexpr auto kMaxSpeed = 4.0_fps;
  constexpr auto kMaxAcceleration = 30.0_fps_sq;

  // Reasonable baseline values for a RAMSETE follower in units of meters and seconds
  constexpr double kRamseteB = 2.0;
  constexpr double kRamseteZeta = 0.7;
}  // namespace AutoConstants

namespace OIConstants
{
  // JLM: This already is handled by OI
  constexpr int kDriverControllerPort = 0;
}  // namespace OIConstants
