// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <units/angle.h>
#include <units/angular_velocity.h>
#include <wpi/math>

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
}  // namespace AutoConstants

namespace DriveConstants
{
    constexpr int kLeftEncoderPorts[]{0,1};
    constexpr int kRightEncoderPorts[]{2,3};
    // Add CAN timeout, wheel diameter, etc.
}  // namespace DriveConstants

namespace IntakeConstants
{
}  // namespace IntakeConstants

namespace ConveyorConstants
{
}  // namespace ConveyorConstants

namespace ClimberConstants
{
}  // namespace ClimberConstants

namespace ShooterConstants
{
}  // namespace ShooterConstants

namespace OIConstants
{
    constexpr int kDriverControllerPort = 1;
}  // namespace OIConstants
