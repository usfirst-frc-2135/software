/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DriveSubsystem.h"

#include <frc/geometry/Rotation2d.h>
#include <frc/kinematics/DifferentialDriveWheelSpeeds.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DriverStation.h>

using namespace DriveConstants;

// JLM: This is what we call the Drivetrain subsystem and most of
// it is already done in our Drivetrain - note what needs to be added
DriveSubsystem::DriveSubsystem() :
  // JLM: These are already declared (with slightly different names and not using these constants)
  m_talon_left1 {kLeftMotor1Port},
  m_talon_left2 {kLeftMotor2Port},
  m_talon_right3 {kRightMotor1Port},
  m_talon_right4 {kRightMotor2Port},
  // JLM: We need to port this into the Drivetrain
  m_odometry {frc::Rotation2d(units::degree_t(GetHeading()))}
  {
    // Reset all peristent values in talons for motor control
    m_talon_left1.ConfigFactoryDefault(30);
    m_talon_left2.ConfigFactoryDefault(30);
    m_talon_right3.ConfigFactoryDefault(30);
    m_talon_right4.ConfigFactoryDefault(30);

    // Set up all left side motors that work together
    // Set both motors to spin opposite for forward
    m_talon_left1.SetInverted(true);
    m_talon_left2.SetInverted(true);
    m_talon_left1.SetNeutralMode(NeutralMode::Brake);   // Don't coast after movements
    m_talon_left2.SetNeutralMode(NeutralMode::Brake);

    // Set up all right side motors that work together
    // Set both motors to spin opposite for forward
    m_talon_right3.SetInverted(true);
    m_talon_right4.SetInverted(true);
    m_talon_right3.SetSensorPhase(true);                // Only if encoders reading backwards
    m_talon_right3.SetNeutralMode(NeutralMode::Brake);  // Don't coast after movements
    m_talon_right4.SetNeutralMode(NeutralMode::Brake);
    ResetEncoders();

    m_talon_left1.SetSafetyEnabled(false);
    m_talon_left2.SetSafetyEnabled(false);
    m_talon_right3.SetSafetyEnabled(false);
    m_talon_right4.SetSafetyEnabled(false);
  }

void DriveSubsystem::Periodic()
{
  // Implementation of subsystem periodic method goes here.
  // JLM: We need to port these into our Drivetrain periodic
  double left_dist = GetDistance(&m_talon_left1);
  double right_dist = GetDistance(&m_talon_right3);
  static int count = 0;
  double gyroAngle = GetHeading();

  // This Periodic function is called every 20 ms
  // JLM: This needs to be ported into Drivetrain periodic
  m_odometry.Update(frc::Rotation2d(units::degree_t(gyroAngle)), units::meter_t(left_dist), units::meter_t(right_dist));
  m_drive.Feed();

  frc::DifferentialDriveWheelSpeeds WheelSpeeds = GetWheelSpeeds();

  // JLM: We probably have something similar that may already work
  frc::SmartDashboard::PutNumber("Left distance", left_dist);
  frc::SmartDashboard::PutNumber("Right distance", right_dist);
  frc::SmartDashboard::PutNumber("Left speed", (double)WheelSpeeds.left);
  frc::SmartDashboard::PutNumber("Right Speed", (double)WheelSpeeds.right);
  frc::SmartDashboard::PutNumber("Gyro angle", gyroAngle);

  if (frc::DriverStation::GetInstance().IsAutonomous() && frc::DriverStation::GetInstance().IsEnabled())
    if ((count++ % 5) == 0) {
      printf("%f, %f, %f\n", left_dist, right_dist, gyroAngle);
    }

  // JLM: We probably have something similar that may already work
  // std::printf("9135:LR cts %5d %5d out %4.2f %4.2f amps %6.3f %6.3f\n",
  //   m_talon_left1.GetSelectedSensorPosition(),
  //   m_talon_right3.GetSelectedSensorPosition(),
  //   m_talon_left1.GetMotorOutputPercent(),
  //   m_talon_right3.GetMotorOutputPercent(),
  //   m_talon_left1.GetOutputCurrent(),
  //   m_talon_right3.GetOutputCurrent()
  // );

  // JLM: We probably have something similar that may already work
  frc::SmartDashboard::PutNumber("left encoder", m_talon_left1.GetSelectedSensorPosition());
  frc::SmartDashboard::PutNumber("right encoder", m_talon_right3.GetSelectedSensorPosition());
  frc::SmartDashboard::PutNumber("L Output Percent", m_talon_left1.GetMotorOutputPercent());
  frc::SmartDashboard::PutNumber("R Output Percent", m_talon_right3.GetMotorOutputPercent());
  frc::SmartDashboard::PutNumber("L Output Current", m_talon_left1.GetOutputCurrent());
  frc::SmartDashboard::PutNumber("R Output Current", m_talon_right3.GetOutputCurrent());
}

// JLM: We already have this (or similar that should be used)
void DriveSubsystem::ArcadeDrive(double fwd, double rot)
{
  m_drive.ArcadeDrive(fwd, rot);
}

void DriveSubsystem::TankDriveVolts(units::volt_t left, units::volt_t right)
{
  m_leftMotors.SetVoltage(left);
  m_rightMotors.SetVoltage(-right);
}

// JLM: We already have this (or similar that should be used)
void DriveSubsystem::ResetEncoders()
{
  m_talon_left1.SetSelectedSensorPosition(0);
  m_talon_right3.SetSelectedSensorPosition(0);
}

// JLM: Probably need to port this into our Drivetrain
double DriveSubsystem::GetAverageEncoderDistance()
{
  return (GetDistance(&m_talon_left1) + GetDistance(&m_talon_right3)) / 2.0;
}

// JLM: We need to port this
void DriveSubsystem::SetMaxOutput(double maxOutput)
{
  m_drive.SetMaxOutput(maxOutput);
}

// JLM: We already have this (or similar that should be used)
double DriveSubsystem::GetHeading()
{
  return std::remainder(m_gyro.GetAngle(), 360) * (kGyroReversed ? -1.0 : 1.0);
}

// JLM: We need to port this
double DriveSubsystem::GetTurnRate()
{
  return m_gyro.GetRate() * (kGyroReversed ? -1.0 : 1.0);
}

// JLM: We need to port this
frc::Pose2d DriveSubsystem::GetPose()
{
  return m_odometry.GetPose();
}

// JLM: We need to port this
frc::DifferentialDriveWheelSpeeds DriveSubsystem::GetWheelSpeeds()
{
  double leftVel = kEncoderDistancePerPulse * (m_talon_left1.GetSelectedSensorVelocity() * 10);
  double rightVel = kEncoderDistancePerPulse * (m_talon_right3.GetSelectedSensorVelocity() * 10);

  return {units::meters_per_second_t(leftVel), units::meters_per_second_t(rightVel)};
}

// JLM: We need to port this
void DriveSubsystem::ResetOdometry(frc::Pose2d pose)
{
  ResetEncoders();
  m_odometry.ResetPosition(pose, frc::Rotation2d(units::degree_t(GetHeading())));
}

// JLM: We need to port this
double DriveSubsystem::GetDistance(WPI_TalonSRX *talon)
{
  return kEncoderDistancePerPulse * talon->GetSelectedSensorPosition();
}
