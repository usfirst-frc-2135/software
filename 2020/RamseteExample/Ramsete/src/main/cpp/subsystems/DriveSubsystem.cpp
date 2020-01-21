/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DriveSubsystem.h"

#include <frc/geometry/Rotation2d.h>
#include <frc/kinematics/DifferentialDriveWheelSpeeds.h>

using namespace DriveConstants;

DriveSubsystem::DriveSubsystem()
    : m_left1{kLeftMotor1Port},
      m_left2{kLeftMotor2Port},
      m_right1{kRightMotor1Port},
      m_right2{kRightMotor2Port},
      m_leftEncoder{kLeftEncoderPorts[0], kLeftEncoderPorts[1]},
      m_rightEncoder{kRightEncoderPorts[0], kRightEncoderPorts[1]},
      m_odometry{frc::Rotation2d(units::degree_t(GetHeading()))},
      m_talon_left1{kLeftMotor1Port},
      m_talon_left2{kLeftMotor2Port},
      m_talon_right3{kRightMotor1Port},
      m_talon_right4{kRightMotor2Port}
       {
  // Set the distance per pulse for the encoders
  m_leftEncoder.SetDistancePerPulse(kEncoderDistancePerPulse);
  m_rightEncoder.SetDistancePerPulse(kEncoderDistancePerPulse);

  ResetEncoders();

  m_talon_left1.SetSensorPhase(true);
  m_talon_left1.SetInverted(true);
  m_talon_left1.SetNeutralMode(NeutralMode::Coast);
  m_talon_left2.Set(ControlMode::Follower, 1);
  m_talon_left2.SetInverted(InvertType::FollowMaster);
  m_talon_left2.SetNeutralMode(NeutralMode::Coast);
  m_talon_right3.SetSensorPhase(true);
  m_talon_right3.SetInverted(true);
  m_talon_right3.SetNeutralMode(NeutralMode::Coast);
  m_talon_right4.Set(ControlMode::Follower, 3);
  m_talon_right4.SetInverted(InvertType::FollowMaster);
  m_talon_right4.SetNeutralMode(NeutralMode::Coast);
}

void DriveSubsystem::Periodic() {
  // Implementation of subsystem periodic method goes here.
  m_odometry.Update(frc::Rotation2d(units::degree_t(GetHeading())),
                    units::meter_t(GetDistance(&m_talon_left1)),
                    units::meter_t(GetDistance(&m_talon_right3)));

}

void DriveSubsystem::ArcadeDrive(double fwd, double rot) {
  m_drive.ArcadeDrive(fwd, rot);
}

void DriveSubsystem::TankDriveVolts(units::volt_t left, units::volt_t right) {
  m_leftMotors.SetVoltage(left);
  m_rightMotors.SetVoltage(-right);
}

void DriveSubsystem::ResetEncoders() {
  SetTalonEncoders(&m_talon_left1, 0),
  SetTalonEncoders(&m_talon_right3, 0);
}

double DriveSubsystem::GetAverageEncoderDistance() {
  return (GetDistance(&m_talon_left1) + GetDistance(&m_talon_right3)) / 2.0;
}

frc::Encoder& DriveSubsystem::GetLeftEncoder() { return m_leftEncoder; }

frc::Encoder& DriveSubsystem::GetRightEncoder() { return m_rightEncoder; }

void DriveSubsystem::SetMaxOutput(double maxOutput) {
  m_drive.SetMaxOutput(maxOutput);
}

double DriveSubsystem::GetHeading() {
  return std::remainder(m_gyro.GetAngle(), 360) * (kGyroReversed ? -1.0 : 1.0);
}

double DriveSubsystem::GetTurnRate() {
  return m_gyro.GetRate() * (kGyroReversed ? -1.0 : 1.0);
}

frc::Pose2d DriveSubsystem::GetPose() { return m_odometry.GetPose(); }

frc::DifferentialDriveWheelSpeeds DriveSubsystem::GetWheelSpeeds() {
  return {units::meters_per_second_t(m_leftEncoder.GetRate()),
          units::meters_per_second_t(m_rightEncoder.GetRate())};
}

void DriveSubsystem::ResetOdometry(frc::Pose2d pose) {
  ResetEncoders();
  m_odometry.ResetPosition(pose,
                           frc::Rotation2d(units::degree_t(GetHeading())));
}

double DriveSubsystem::GetDistance(WPI_TalonSRX *talon) {
  double distance = kEncoderDistancePerPulse * talon->GetSelectedSensorPosition();
  int id = talon->GetDeviceID();
  printf("ID: %d has value %f\n", id, distance);
  return distance;
}

void DriveSubsystem::SetTalonEncoders(WPI_TalonSRX *talon, double value) {
  talon->SetSelectedSensorPosition(value);
}
