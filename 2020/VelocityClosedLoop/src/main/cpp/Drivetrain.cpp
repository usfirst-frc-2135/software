/**
 * Phoenix Software License Agreement
 *
 * Copyright (C) Cross The Road Electronics.  All rights
 * reserved.
 * 
 * Cross The Road Electronics (CTRE) licenses to you the right to 
 * use, publish, and distribute copies of CRF (Cross The Road) firmware files (*.crf) and 
 * Phoenix Software API Libraries ONLY when in use with CTR Electronics hardware products
 * as well as the FRC roboRIO when in use in FRC Competition.
 * 
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * CROSS THE ROAD ELECTRONICS BE LIABLE FOR ANY INCIDENTAL, SPECIAL, 
 * INDIRECT OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE
 */
/**
 * Example demonstrating the velocity closed-loop servo.
 * Tested with Logitech F350 USB Gamepad inserted into Driver Station]
 *
 * Be sure to select the correct feedback sensor using configSelectedFeedbackSensor() below.
 *
 * After deploying/debugging this to your RIO, first use the left Y-stick
 * to throttle the Talon manually.  This will confirm your hardware setup.
 * Be sure to confirm that when the Talon is driving forward (green) the
 * position sensor is moving in a positive direction.  If this is not the cause
 * flip the boolean input to the SetSensorPhase() call below.
 *
 * Once you've ensured your feedback device is in-phase with the motor,
 * use the button shortcuts to servo to target velocity.
 *
 * Tweak the PID gains accordingly.
 */
#include <iostream>
#include <string>

#include "Drivetrain.h"
#include <frc/drive/DifferentialDrive.h>
#include <frc/commands/Subsystem.h>
#include "ctre/Phoenix.h"
#include "Constants.h"


Drivetrain::Drivetrain()
: frc::Subsystem("Drivetrain")
{

	_L1talon = new WPI_TalonSRX(1);
	_L2talon = new WPI_TalonSRX(2);
	_R3talon = new WPI_TalonSRX(3);
	_R4talon = new WPI_TalonSRX(4);

	// Code copied from Robot2019-Imported
	  
    _diffDrive.reset(new frc::DifferentialDrive(*_L1talon, *_R3talon));
        	
	  // If either master drive talons are valid, enable safety timer
    _diffDrive->SetSafetyEnabled(_L1talon || _R3talon);
	void DrivetrainInit();
};
//	Automatic Drive Spin movement

// void Robot::MoveSpin(bool spinRight) {
	// double spinSpeed = m_driveSpin;

	// if (!spinRight)
		// spinSpeed *= -1.0;

	// if (_L1talon || _R3talon)
		// _diffDrive->TankDrive(spinSpeed, -spinSpeed, false);
//}

// void Robot::MoveStop() {
	// if (_L1talon || _R3talon)
		// _diffDrive->TankDrive(0.0, 0.0, false);
// }

	void Drivetrain::DrivetrainInit() {

		AddChild("Diff Drive", _diffDrive);
 		_diffDrive->SetSafetyEnabled(true);
    	_diffDrive->SetExpiration(0.25);
    	_diffDrive->SetMaxOutput(1.0);
		//L1

		_L1talon->ConfigFactoryDefault();
		_L1talon->SetInverted(true);
        /* first choose the sensor */
		_L1talon->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, kTimeoutMs);
		_L1talon->SetSensorPhase(true);

		/* set the peak and nominal outputs */
		_L1talon->ConfigNominalOutputForward(0, kTimeoutMs);
		_L1talon->ConfigNominalOutputReverse(0, kTimeoutMs);
		_L1talon->ConfigPeakOutputForward(1, kTimeoutMs);
		_L1talon->ConfigPeakOutputReverse(-1, kTimeoutMs);
		/* set closed loop gains in slot0 */
		_L1talon->Config_kF(kPIDLoopIdx, 0.1097, kTimeoutMs);
		_L1talon->Config_kP(kPIDLoopIdx, 0.22, kTimeoutMs);
		_L1talon->Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
		_L1talon->Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);
	
		

		//L2
		_L2talon->ConfigFactoryDefault();
		_L2talon->Set(ControlMode::Follower, 1);
    	_L2talon->SetInverted(InvertType::FollowMaster);
		
		//R3
		_R3talon->ConfigFactoryDefault();
		_R3talon->SetInverted(false);
        /* first choose the sensor */
		_R3talon->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, kTimeoutMs);
		_R3talon->SetSensorPhase(true);

		/* set the peak and nominal outputs */
		_R3talon->ConfigNominalOutputForward(0, kTimeoutMs);
		_R3talon->ConfigNominalOutputReverse(0, kTimeoutMs);
		_R3talon->ConfigPeakOutputForward(1, kTimeoutMs);
		_R3talon->ConfigPeakOutputReverse(-1, kTimeoutMs);
		/* set closed loop gains in slot0 */
		_R3talon->Config_kF(kPIDLoopIdx, 0.1097, kTimeoutMs);
		_R3talon->Config_kP(kPIDLoopIdx, 0.22, kTimeoutMs);
		_R3talon->Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
		_R3talon->Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);

		//R4
		_R4talon->ConfigFactoryDefault();
		_R4talon->Set(ControlMode::Follower, 3);
    	_R4talon->SetInverted(InvertType::FollowMaster);

	}

void Drivetrain::Periodic() {
    // Put code here to be run every loop
	//static int 	i = 0;
    //int			encoderLeft = 0;
	//int			encoderRight = 0;
 	//double  	heading = 0.0;
    //const int   pidIndex = 0;					   // PID slot index for sensors


		//encoderLeft = _L1talon->GetSelectedSensorPosition(pidIndex);

		//encoderRight = _R3talon->GetSelectedSensorPosition(pidIndex);

	//heading = GetIMUHeading();

	//frc::SmartDashboard::PutNumber("DT_Encoder_L", encoderLeft);
	//frc::SmartDashboard::PutNumber("DT_Encoder_R", encoderRight);
	//frc::SmartDashboard::PutNumber("DT_Heading", heading);

    //if (m_driveDebug > 1 || (m_driveDebug > 0 && m_isMovingAuto)) {

		// SLow debug message rate to every 5 * 20ms periods
		//if (i++ % 5 == 0) {
			//double	outputL1 = 0.0, currentL1 = 0.0, currentL2 = 0.0;
			//double	outputR3 = 0.0, currentR3 = 0.0, currentR4 = 0.0;

			
				//outputL1 = _L1talon->GetMotorOutputPercent();
				//currentL1 = _L1talon->GetOutputCurrent();

				//currentL2 = _L2talon->GetOutputCurrent();

				//outputR3 = _R3talon->GetMotorOutputPercent();
				//currentR3 = _R3talon->GetOutputCurrent();

				//currentR4 = _R4talon->GetOutputCurrent();

			//double secs = (double)frc::RobotController::GetFPGATime() / 1000000.0;

			//std::printf("2135: DT %6.3f deg %4.1f turn %4.1f LR cts %5d %5d out %4.2f %4.2f amps %6.3f %6.3f %6.3f %6.3f\n",
				//secs, heading, m_turnAngle, encoderLeft, encoderRight, outputL1, outputR3, currentL1, currentL2, currentR3, currentR4);

			//frc::SmartDashboard::PutNumber("DT_Output_L1", outputL1);
			//frc::SmartDashboard::PutNumber("DT_Current_L1", currentL1);
			//frc::SmartDashboard::PutNumber("DT_Current_L2", currentL2);

			//frc::SmartDashboard::PutNumber("DT_Output_R3", outputR3);
			//frc::SmartDashboard::PutNumber("DT_Current_R3", currentR3);
			//frc::SmartDashboard::PutNumber("DT_Current_R4", currentR4);
	//	}
//	}
}