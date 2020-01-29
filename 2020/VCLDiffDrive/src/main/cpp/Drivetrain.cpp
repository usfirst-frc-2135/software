/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivetrain.h"

Drivetrain::Drivetrain() : frc::Subsystem("Drivetrain") {

	m_gyro.Reset();
    // Set the distance per pulse for the drive encoders. We can simply use the
    // distance traveled for one rotation of the wheel divided by the encoder
    // resolution.
    m_leftEncoder.SetDistancePerPulse(2 * wpi::math::pi * kWheelRadius /
        kEncoderResolution);
    m_rightEncoder.SetDistancePerPulse(2 * wpi::math::pi * kWheelRadius /
        kEncoderResolution);

    m_leftEncoder.Reset();
    m_rightEncoder.Reset();

	// Talons

	m_L1talon = new WPI_TalonSRX(1);
	m_L2talon = new WPI_TalonSRX(2);
	m_R3talon = new WPI_TalonSRX(3);
	m_R4talon = new WPI_TalonSRX(4);

	// Code copied from Robot2019-Imported
	  
    _diffDrive.reset(new frc::DifferentialDrive(*m_L1talon, *m_R3talon));
        	
	  // If either master drive talons are valid, enable safety timer
    _diffDrive->SetSafetyEnabled(m_L1talon || m_R3talon);
}

void Drivetrain::DrivetrainInit() {

		AddChild("Diff Drive", _diffDrive);
 		_diffDrive->SetSafetyEnabled(true);
    	_diffDrive->SetExpiration(0.25);
    	_diffDrive->SetMaxOutput(1.0);
		//L1

		m_L1talon->ConfigFactoryDefault();
		m_L1talon->SetInverted(true);
        /* first choose the sensor */
		m_L1talon->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, kTimeoutMs);
		m_L1talon->SetSensorPhase(true);

		/* set the peak and nominal outputs */
		m_L1talon->ConfigNominalOutputForward(0, kTimeoutMs);
		m_L1talon->ConfigNominalOutputReverse(0, kTimeoutMs);
		m_L1talon->ConfigPeakOutputForward(1, kTimeoutMs);
		m_L1talon->ConfigPeakOutputReverse(-1, kTimeoutMs);
		/* set closed loop gains in slot0 */
		m_L1talon->Config_kF(kPIDLoopIdx, 0.1097, kTimeoutMs);
		m_L1talon->Config_kP(kPIDLoopIdx, 0.22, kTimeoutMs);
		m_L1talon->Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
		m_L1talon->Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);

		//L2
		m_L2talon->ConfigFactoryDefault();
		m_L2talon->Set(ControlMode::Follower, 1);
    	m_L2talon->SetInverted(InvertType::FollowMaster);
		
		//R3
		m_R3talon->ConfigFactoryDefault();
		m_R3talon->SetInverted(false);
        /* first choose the sensor */
		m_R3talon->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, kTimeoutMs);
		m_R3talon->SetSensorPhase(true);

		/* set the peak and nominal outputs */
		m_R3talon->ConfigNominalOutputForward(0, kTimeoutMs);
		m_R3talon->ConfigNominalOutputReverse(0, kTimeoutMs);
		m_R3talon->ConfigPeakOutputForward(1, kTimeoutMs);
		m_R3talon->ConfigPeakOutputReverse(-1, kTimeoutMs);
		/* set closed loop gains in slot0 */
		m_R3talon->Config_kF(kPIDLoopIdx, 0.1097, kTimeoutMs);
		m_R3talon->Config_kP(kPIDLoopIdx, 0.22, kTimeoutMs);
		m_R3talon->Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
		m_R3talon->Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);

		//R4
		m_R4talon->ConfigFactoryDefault();
		m_R4talon->Set(ControlMode::Follower, 3);
    	m_R4talon->SetInverted(InvertType::FollowMaster);

	}

void Drivetrain::Periodic() {
    // Put code here to be run every loop
	// static int 	i = 0;
  // int			encoderLeft = 0;
	// int			encoderRight = 0;
 	// double  	heading = 0.0;
  // const int   pidIndex = 0;					   // PID slot index for sensors


	// 	encoderLeft = m_L1talon->GetSelectedSensorPosition(pidIndex);

	// 	encoderRight = m_R3talon->GetSelectedSensorPosition(pidIndex);

	// heading = GetIMUHeading();

	// frc::SmartDashboard::PutNumber("DT_Encoder_L", encoderLeft);
	// frc::SmartDashboard::PutNumber("DT_Encoder_R", encoderRight);
	// frc::SmartDashboard::PutNumber("DT_Heading", heading);

  //   if (m_driveDebug > 1 || (m_driveDebug > 0 && m_isMovingAuto)) {

	// 	Slow debug message rate to every 5 * 20ms periods
	// 	if (i++ % 5 == 0) {
	// 		double	outputL1 = 0.0, currentL1 = 0.0, currentL2 = 0.0;
	// 		double	outputR3 = 0.0, currentR3 = 0.0, currentR4 = 0.0;

			
	// 		  outputL1 = m_L1talon->GetMotorOutputPercent();
	// 			currentL1 = m_L1talon->GetOutputCurrent();

	// 			currentL2 = m_L2talon->GetOutputCurrent();

	// 			outputR3 = m_R3talon->GetMotorOutputPercent();
	// 			currentR3 = m_R3talon->GetOutputCurrent();

	// 			currentR4 = m_R4talon->GetOutputCurrent();

	// 		double secs = (double)frc::RobotController::GetFPGATime() / 1000000.0;

	// 		std::printf("2135: DT %6.3f deg %4.1f turn %4.1f LR cts %5d %5d out %4.2f %4.2f amps %6.3f %6.3f %6.3f %6.3f\n",
	// 			secs, heading, m_turnAngle, encoderLeft, encoderRight, outputL1, outputR3, currentL1, currentL2, currentR3, currentR4);

	// 		frc::SmartDashboard::PutNumber("DT_Output_L1", outputL1);
	// 		frc::SmartDashboard::PutNumber("DT_Current_L1", currentL1);
	// 		frc::SmartDashboard::PutNumber("DT_Current_L2", currentL2);

	// 		frc::SmartDashboard::PutNumber("DT_Output_R3", outputR3);
	// 		frc::SmartDashboard::PutNumber("DT_Current_R3", currentR3);
	// 		frc::SmartDashboard::PutNumber("DT_Current_R4", currentR4);
	// 	}
	// }
}

void Drivetrain::SetSpeeds(const frc::DifferentialDriveWheelSpeeds& speeds) {
  const auto leftOutput = m_leftPIDController.Calculate(
      m_leftEncoder.GetRate(), speeds.left.to<double>());
  const auto rightOutput = m_rightPIDController.Calculate(
      m_rightEncoder.GetRate(), speeds.right.to<double>());

  m_leftGroup.Set(leftOutput);
  m_rightGroup.Set(rightOutput);
}

void Drivetrain::Drive(units::meters_per_second_t xSpeed,
                       units::radians_per_second_t rot) {
  SetSpeeds(m_kinematics.ToWheelSpeeds({xSpeed, 0_mps, rot}));
}

void Drivetrain::UpdateOdometry() {
  m_odometry.Update(GetAngle(), units::meter_t(m_leftEncoder.GetDistance()),
                    units::meter_t(m_rightEncoder.GetDistance()));
}
