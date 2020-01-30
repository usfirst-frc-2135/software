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

using namespace DriveConstants;

DriveSubsystem::DriveSubsystem() :
  //   m_left1{kLeftMotor1Port},
  //   m_left2{kLeftMotor2Port},
  //   m_right1{kRightMotor1Port},
  //   m_right2{kRightMotor2Port},
  m_talon_left1{kLeftMotor1Port},
  m_talon_left2{kLeftMotor2Port},
  m_talon_right3{kRightMotor1Port},
  m_talon_right4{kRightMotor2Port},
 // m_leftEncoder{kLeftEncoderPorts[0], kLeftEncoderPorts[1]},
 // m_rightEncoder{kRightEncoderPorts[0], kRightEncoderPorts[1]},
  m_odometry{frc::Rotation2d(units::degree_t(GetHeading()))}
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
    //m_talon_left1.SetSensorPhase(true);               // Only if encoders reading backwards
    m_talon_left1.SetNeutralMode(NeutralMode::Brake);   // Don't coast after movements
    m_talon_left2.SetNeutralMode(NeutralMode::Brake);
    // This example deals with all motors individually--does not master/slave in talons
    //m_talon_left2.Set(ControlMode::Follower, 1);
    //m_talon_left2.SetInverted(InvertType::FollowMaster);

    // Set up all right side motors that work together
    // Set both motors to spin opposite for forward
    m_talon_right3.SetInverted(true);
    m_talon_right4.SetInverted(true);
    m_talon_right3.SetSensorPhase(true);               // Only if encoders reading backwards
    m_talon_right3.SetNeutralMode(NeutralMode::Brake);   // Don't coast after movements
    m_talon_right4.SetNeutralMode(NeutralMode::Brake);
    // This example deals with all motors individually--does not master/slave in talons
    //m_talon_right4.Set(ControlMode::Follower, 3);
    //m_talon_right4.SetInverted(InvertType::FollowMaster);

    // Set the distance per pulse for the encoders
    //m_leftEncoder.SetDistancePerPulse(kEncoderDistancePerPulse);
    //m_rightEncoder.SetDistancePerPulse(kEncoderDistancePerPulse);

    m_talon_left1.SetSelectedSensorPosition(0);
    m_talon_right3.SetSelectedSensorPosition(0);
  }

void DriveSubsystem::Periodic() {
  // Implementation of subsystem periodic method goes here.
  double left_dist = GetDistance(&m_talon_left1);
  double right_dist = GetDistance(&m_talon_right3);
  static int count = 0;
  double gyroAngle = GetHeading();

  // This Periodic function is called every 20 ms
  m_odometry.Update(frc::Rotation2d(units::degree_t(gyroAngle)),
                    units::meter_t(left_dist),
                    units::meter_t(right_dist)
    );

  m_drive.Feed();

  frc::DifferentialDriveWheelSpeeds WheelSpeeds = GetWheelSpeeds(); 

  frc::SmartDashboard::PutNumber("Gyro angle", gyroAngle);
  frc::SmartDashboard::PutNumber("Left distance", left_dist);
  frc::SmartDashboard::PutNumber("Right distance", right_dist);
  frc::SmartDashboard::PutNumber("Left speed", (double)WheelSpeeds.left);
  frc::SmartDashboard::PutNumber("Right Speed", (double)WheelSpeeds.right);

  if ((count++ % 5) == 0) {
    printf("%f, %f\n", left_dist, right_dist);
  }
}

void DriveSubsystem::ArcadeDrive(double fwd, double rot) {
  m_drive.ArcadeDrive(fwd, rot);
}

void DriveSubsystem::TankDriveVolts(units::volt_t left, units::volt_t right) {
  m_leftMotors.SetVoltage(left);
  m_rightMotors.SetVoltage(-right);
}

void DriveSubsystem::ResetEncoders() {
  m_talon_left1.SetSelectedSensorPosition(0);
  m_talon_right3.SetSelectedSensorPosition(0);
}

double DriveSubsystem::GetAverageEncoderDistance() {
  return (GetDistance(&m_talon_left1) + GetDistance(&m_talon_right3)) / 2.0;
}

// frc::Encoder& DriveSubsystem::GetLeftEncoder() {
//    return m_talon_left1.GetSelectedSensorPosition(0);
// }

// frc::Encoder& DriveSubsystem::GetRightEncoder() {
//    return m_talon_right3.GetSelectedSensorPosition(0);
// }

void DriveSubsystem::SetMaxOutput(double maxOutput) {
  m_drive.SetMaxOutput(maxOutput);
}

double DriveSubsystem::GetHeading() {
  return std::remainder(m_gyro.GetAngle(), 360) * (kGyroReversed ? -1.0 : 1.0);
}

double DriveSubsystem::GetTurnRate() {
  return m_gyro.GetRate() * (kGyroReversed ? -1.0 : 1.0);
}

frc::Pose2d DriveSubsystem::GetPose() {
  return m_odometry.GetPose();
}

frc::DifferentialDriveWheelSpeeds DriveSubsystem::GetWheelSpeeds() {
  // return {units::meters_per_second_t(m_leftEncoder.GetRate()),
          // units::meters_per_second_t(m_rightEncoder.GetRate())
  double leftVel = kEncoderDistancePerPulse * (m_talon_left1.GetSelectedSensorVelocity() * 10);
  double rightVel = kEncoderDistancePerPulse * (m_talon_right3.GetSelectedSensorVelocity() * 10);

  return {units::meters_per_second_t(leftVel), units::meters_per_second_t(rightVel)};
}


void DriveSubsystem::ResetOdometry(frc::Pose2d pose) {
  ResetEncoders();
  m_odometry.ResetPosition(pose, frc::Rotation2d(units::degree_t(GetHeading())));
}

double DriveSubsystem::GetDistance(WPI_TalonSRX *talon) {
  return kEncoderDistancePerPulse * talon->GetSelectedSensorPosition();
}

// void DriveSubsystem::CoastAndStop() {
//   m_talon_left1.SetVoltage(0_V);
//   m_talon_left2.SetVoltage(0_V);
//   m_talon_right3.SetVoltage(0_V);
//   m_talon_right4.SetVoltage(0_V);

//   m_talon_left1.SetNeutralMode(NeutralMode::Coast);
//   m_talon_left2.SetNeutralMode(NeutralMode::Coast);
//   m_talon_right3.SetNeutralMode(NeutralMode::Coast);
//   m_talon_right4.SetNeutralMode(NeutralMode::Coast);
// }

// double DriveSubsystem::CountsToMeters(int counts) {
//   double meters;
//   meters = ((double) counts / COUNTS_PER_ROTATION) * m_circumMeters;
//   return meters;
// }
