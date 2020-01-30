/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <iostream>
#include <string>

#include <frc/drive/DifferentialDrive.h>

#include <ctre/Phoenix.h>

#include <frc/AnalogGyro.h>
#include <frc/Encoder.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/controller/PIDController.h>
#include <frc/kinematics/DifferentialDriveKinematics.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>
#include <units/units.h>
#include <wpi/math>
#include <frc/Joystick.h>
#include <frc/commands/Subsystem.h>

/**
 * Represents a differential drive style drivetrain.
 */
class Drivetrain: public frc::Subsystem {
 public:
  Drivetrain();
  	void DrivetrainInit();
	void Periodic();
  	void SetSpeeds(const frc::DifferentialDriveWheelSpeeds& speeds);
	void Drive(units::meters_per_second_t xSpeed,
				units::radians_per_second_t rot);
	void UpdateOdometry();

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


  private:
	std::shared_ptr<frc::Joystick> dStick2;
		bool m_separateJoysticks = false;

	static constexpr units::meter_t kTrackWidth = 0.381_m * 2;
	static constexpr double kWheelRadius = 0.0508;  // meters
	static constexpr int kEncoderResolution = 4096;

	std::shared_ptr<frc::DifferentialDrive> _diffDrive;
		WPI_TalonSRX *m_L1talon;
		WPI_TalonSRX *m_L2talon;
		WPI_TalonSRX *m_R3talon;
		WPI_TalonSRX *m_R4talon;

	frc::Encoder m_leftEncoder{0, 1};
	frc::Encoder m_rightEncoder{2, 3};

  

	frc2::PIDController m_leftPIDController{1.0, 0.0, 0.0};
	frc2::PIDController m_rightPIDController{1.0, 0.0, 0.0};

	frc::AnalogGyro m_gyro{0};

	frc::DifferentialDriveKinematics m_kinematics{kTrackWidth};
	frc::DifferentialDriveOdometry m_odometry{GetAngle()};

	// Declare Variables 
	double kTimeoutMs = 10; 
	double kPIDLoopIdx = 0; 


	//Declare Module Variables 
  
};
