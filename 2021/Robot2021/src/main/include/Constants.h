// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/controller/SimpleMotorFeedforward.h>
#include <frc/kinematics/DifferentialDriveKinematics.h>
#include <units/acceleration.h>
#include <units/angular_velocity.h>
#include <units/angular_acceleration.h>
#include <units/length.h>
#include <units/velocity.h>
#include <wpi/math>

using namespace units;
using namespace units::acceleration;
using namespace units::length;
using namespace units::velocity;

/**
 * The Constants header provides a convenient place for teams to hold robot-wide
 * numerical or bool constants.  This should not be used for any other purpose.
 *
 * It is generally a good idea to place constants into subsystem- or
 * command-specific namespaces within this header, which can then be used where
 * they are needed.
 */

namespace AutoConstants
{
} // namespace AutoConstants

namespace DriveConstants
{
    static constexpr int kLeftEncoderPorts[]{ 1, 2 };
    static constexpr int kRightEncoderPorts[]{ 3, 4 };

    // Odometry constants
    static constexpr int kEncoderCPR = 2048;               // CPR is 2048 for new TalonFX
    static constexpr meter_t kWheelDiaMeters = 6.0_in;     // Units library does the conversion
    static constexpr meter_t kEncoderMetersPerCount =
        (kWheelDiaMeters * wpi::math::pi) / static_cast<double>(kEncoderCPR);
    static constexpr meter_t kTrackWidthMeters = 0.6477_m; // Measured track width
    static constexpr double kGearRatio = 13.94;            // Gear reduction

    // Kinematics values for 2135 Bebula - 2019 B-bot
    static constexpr auto ks = 0.899_V;
    static constexpr auto kv = 1.411_V / 1_mps;
    static constexpr auto ka = 0.21_V / 1_mps_sq;
    static constexpr auto KvAngular = 1.5_V / 1_rad_per_s;
    static constexpr auto KaAngular = 0.3_V / 1_rad_per_s_sq;

    static constexpr double kPDriveVel = 0.00291;
    static constexpr meters_per_second_t kMaxSpeed = 1.1336_mps;
    static constexpr meters_per_second_squared_t kMaxAcceleration = 10.668_mps_sq;

    // Reasonable baseline values for a RAMSETE follower in meters and seconds
    static constexpr double kRamseteB = 2.0;
    static constexpr double kRamseteZeta = 0.7;

} // namespace DriveConstants

namespace IntakeConstants
{
} // namespace IntakeConstants

namespace ConveyorConstants
{
} // namespace ConveyorConstants

namespace ClimberConstants
{
} // namespace ClimberConstants

namespace ShooterConstants
{
} // namespace ShooterConstants

namespace OIConstants
{
} // namespace OIConstants
