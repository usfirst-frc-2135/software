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
#include <frc/controller/SimpleMotorFeedforward.h>
#include <ctre/Phoenix.h>

#include <frc/controller/PIDController.h>
#include <frc/kinematics/DifferentialDriveKinematics.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>
#include <units/units.h>
#include <wpi/math>

/**
 * Represents a differential drive style drivetrain.
 */
class Drivetrain
{
  public:
    Drivetrain()
    {
      m_gyro.Reset();

      // Reset all peristent values in talons for motor control
      m_leftMaster.ConfigFactoryDefault(30);
      m_leftFollower.ConfigFactoryDefault(30);
      m_rightMaster.ConfigFactoryDefault(30);
      m_rightFollower.ConfigFactoryDefault(30);

      // Don't coast after movements
      m_leftMaster.SetNeutralMode(NeutralMode::Coast);
      m_rightMaster.SetNeutralMode(NeutralMode::Coast);
      m_leftFollower.SetNeutralMode(NeutralMode::Coast);
      m_rightFollower.SetNeutralMode(NeutralMode::Coast);

      // Set up all left side motors that work together
      // Set both motors to spin opposite for forward
      m_leftMaster.SetInverted(true);
      m_leftMaster.SetSensorPhase(true); //true makes the left run in the correct direction
      m_leftFollower.Set(ControlMode::Follower, 1);
      m_leftFollower.SetInverted(InvertType::FollowMaster);

      // Set up all right side motors that work together
      // Set both motors to spin opposite for forward
      m_rightMaster.SetInverted(true);
      m_rightMaster.SetSensorPhase(false); //false makes the right run in the correct direction
      m_rightFollower.Set(ControlMode::Follower, 3);
      m_rightFollower.SetInverted(InvertType::FollowMaster);

      m_leftMaster.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative);
      m_rightMaster.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative);

      // Reset encoders
      m_leftMaster.SetSelectedSensorPosition(0);
      m_rightMaster.SetSelectedSensorPosition(0);
    }

    // Get the robot angle as a Rotation2d.
    frc::Rotation2d GetAngle() const
    {
      // Negating the angle because WPILib Gyros are CW positive.
      return frc::Rotation2d(units::degree_t(-m_gyro.GetAngle()));
    }
    double GetDistance(WPI_TalonSRX *talon);
    double GetSpeed(WPI_TalonSRX *talon);

    // JLM: 7fps = 2.15mps
    static constexpr units::meters_per_second_t kMaxSpeed = 2.3_mps;  //Changed from 3 meters per second
    static constexpr units::radians_per_second_t kMaxAngularSpeed { wpi::math::pi } ;  // 1/2 rotation per second

    void Periodic();
    void UpdateOdometry();
    void SetSpeeds(const frc::DifferentialDriveWheelSpeeds& speeds);
    void Drive(units::meters_per_second_t ySpeed, units::radians_per_second_t rot);

  private:
    static constexpr units::meter_t kTrackWidth = 0.6096_m;
    static constexpr double kWheelDiameter = 0.1524;  // meters
    static constexpr int kEncoderResolution = 4096;

    // Assumes the encoders are directly mounted on the wheel shafts
    static constexpr double kEncoderDistancePerPulse =
      (kWheelDiameter * wpi::math::pi) / static_cast<double>(kEncoderResolution);

    WPI_TalonSRX m_leftMaster { 1 };
    WPI_TalonSRX m_leftFollower { 2 };
    WPI_TalonSRX m_rightMaster { 3 };
    WPI_TalonSRX m_rightFollower { 4 };

    frc::Encoder m_leftEncoder { 0, 1 };
    frc::Encoder m_rightEncoder { 2, 3 };

    frc2::PIDController m_leftPIDController { 0.6, 0.0, 0.0 };
    frc2::PIDController m_rightPIDController { 0.6, 0.0, 0.0 };

    frc::AnalogGyro m_gyro { 0 };

    frc::DifferentialDriveKinematics m_kinematics { kTrackWidth };
    frc::DifferentialDriveOdometry m_odometry { GetAngle() };

    // JLM: I don't believe kS is really 2.0V, since we measured 0.866 (or something similar) during characterization
    // JLM: kV and kA (not set here) should come from characterization?
    frc::SimpleMotorFeedforward<units::meters> m_feedforward { 0.866_V, 3.7_V / 1_mps }; //original: 1.0_V, 3_V / 1_mps
};
