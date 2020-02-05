/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/AnalogGyro.h>
#include <frc/Encoder.h>
#include <frc/SpeedControllerGroup.h>
#include <ctre/Phoenix.h>

#include <frc/controller/PIDController.h>
#include <frc/kinematics/DifferentialDriveKinematics.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>
#include <units/units.h>
#include <wpi/math>

/**
 * Represents a differential drive style drivetrain.
 */
class Drivetrain {
 public:
  Drivetrain() {
    m_gyro.Reset();
     // Reset all peristent values in talons for motor control
    m_leftMaster.ConfigFactoryDefault(30);
    m_leftFollower.ConfigFactoryDefault(30);
    m_rightMaster.ConfigFactoryDefault(30);
    m_rightFollower.ConfigFactoryDefault(30);

    // Set up all left side motors that work together
    // Set both motors to spin opposite for forward
    m_leftMaster.SetInverted(true);
    m_leftFollower.SetInverted(true);

    // Set up all right side motors that work together
    // Set both motors to spin opposite for forward
    m_rightMaster.SetInverted(true);
    m_rightFollower.SetInverted(true);
    m_rightMaster.SetSensorPhase(true);               // Only if encoders reading backwards
    
    m_leftFollower.Set(ControlMode::Follower, 1);
    m_leftFollower.SetInverted(InvertType::FollowMaster);

    m_rightFollower.Set(ControlMode::Follower, 3);
    m_rightFollower.SetInverted(InvertType::FollowMaster);

    m_leftMaster.SetSelectedSensorPosition(0);
    m_rightMaster.SetSelectedSensorPosition(0);
  
    // Set the distance per pulse for the drive encoders. We can simply use the
    // distance traveled for one rotation of the wheel divided by the encoder
    // resolution.
    //m_leftEncoder.SetDistancePerPulse(2 * wpi::math::pi * kWheelRadius /
                                      //kEncoderResolution);
    //m_rightEncoder.SetDistancePerPulse(2 * wpi::math::pi * kWheelRadius /
                                       //kEncoderResolution);

    //m_leftEncoder.Reset();
    //m_rightEncoder.Reset();
  }
    

  /**
   * Get the robot angle as a Rotation2d.
   */
  frc::Rotation2d GetAngle() const {
    // Negating the angle because WPILib Gyros are CW positive.
    return frc::Rotation2d(units::degree_t(-m_gyro.GetAngle()));
  }

  static constexpr units::meters_per_second_t kMaxSpeed =
      3.0_mps;  // 3 meters per second
  static constexpr units::radians_per_second_t kMaxAngularSpeed{
      wpi::math::pi};  // 1/2 rotation per second

  void SetSpeeds(const frc::DifferentialDriveWheelSpeeds& speeds);
  void Drive(units::meters_per_second_t xSpeed,
             units::radians_per_second_t rot);
  void UpdateOdometry();
  double GetDistance(WPI_TalonSRX *talon);
  double GetSpeed(WPI_TalonSRX *talon);

 private:
  static constexpr units::meter_t kTrackWidth = 0.6096_m;
  static constexpr double kWheelDiameter = 0.1524;  // meters
  static constexpr int kEncoderResolution = 4096;
  static constexpr double kEncoderDistancePerPulse =
    // Assumes the encoders are directly mounted on the wheel shafts
    (kWheelDiameter * wpi::math::pi) / static_cast<double>(kEncoderResolution);

  WPI_TalonSRX m_leftMaster{1};
  WPI_TalonSRX m_leftFollower{2};
  WPI_TalonSRX m_rightMaster{3};
  WPI_TalonSRX m_rightFollower{4};

  frc::SpeedControllerGroup m_leftGroup{m_leftMaster, m_leftFollower};
  frc::SpeedControllerGroup m_rightGroup{m_rightMaster, m_rightFollower};

  frc::Encoder m_leftEncoder{0, 1};
  frc::Encoder m_rightEncoder{2, 3};

  frc2::PIDController m_leftPIDController{1.0, 0.0, 0.0};
  frc2::PIDController m_rightPIDController{1.0, 0.0, 0.0};

  frc::AnalogGyro m_gyro{0};

  frc::DifferentialDriveKinematics m_kinematics{kTrackWidth};
  frc::DifferentialDriveOdometry m_odometry{GetAngle()};
};
