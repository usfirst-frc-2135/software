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

#include "frc/WPILib.h"
#include "ctre/Phoenix.h"
#include "Constants.h"

using namespace frc;

class Robot: public TimedRobot {
public:
	TalonSRX *L1_talon = new TalonSRX(1);
	TalonSRX *L2_talon = new TalonSRX(2);
	TalonSRX *R3_talon = new TalonSRX(3);
	TalonSRX *R4_talon = new TalonSRX(4);
	Joystick *_joy = new Joystick(0);
	std::string _sb;
	int _loops = 0;

	void RobotInit() {
		//L1

		L1_talon->ConfigFactoryDefault();
		L1_talon->SetInverted(true);
        /* first choose the sensor */
		L1_talon->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, kTimeoutMs);
		L1_talon->SetSensorPhase(true);

		/* set the peak and nominal outputs */
		L1_talon->ConfigNominalOutputForward(0, kTimeoutMs);
		L1_talon->ConfigNominalOutputReverse(0, kTimeoutMs);
		L1_talon->ConfigPeakOutputForward(1, kTimeoutMs);
		L1_talon->ConfigPeakOutputReverse(-1, kTimeoutMs);
		/* set closed loop gains in slot0 */
		L1_talon->Config_kF(kPIDLoopIdx, 0.1097, kTimeoutMs);
		L1_talon->Config_kP(kPIDLoopIdx, 0.22, kTimeoutMs);
		L1_talon->Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
		L1_talon->Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);
	
		

		//L2
		L2_talon->ConfigFactoryDefault();
		L2_talon->Set(ControlMode::Follower, 1);
    	L2_talon->SetInverted(InvertType::FollowMaster);
		
		//R3
		R3_talon->ConfigFactoryDefault();
		R3_talon->SetInverted(false);
        /* first choose the sensor */
		R3_talon->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, kTimeoutMs);
		R3_talon->SetSensorPhase(true);

		/* set the peak and nominal outputs */
		R3_talon->ConfigNominalOutputForward(0, kTimeoutMs);
		R3_talon->ConfigNominalOutputReverse(0, kTimeoutMs);
		R3_talon->ConfigPeakOutputForward(1, kTimeoutMs);
		R3_talon->ConfigPeakOutputReverse(-1, kTimeoutMs);
		/* set closed loop gains in slot0 */
		R3_talon->Config_kF(kPIDLoopIdx, 0.1097, kTimeoutMs);
		R3_talon->Config_kP(kPIDLoopIdx, 0.22, kTimeoutMs);
		R3_talon->Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
		R3_talon->Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);

		//R4
		R4_talon->ConfigFactoryDefault();
		R4_talon->Set(ControlMode::Follower, 3);
    	R4_talon->SetInverted(InvertType::FollowMaster);

	}


	/**
	 * This function is called periodically during operator control
	 */
	void TeleopPeriodic() {
		/* get gamepad axis */
		double leftYstick = _joy->GetY();
		double L1_motorOutput = L1_talon->GetMotorOutputPercent();
		//double L2_motorOutput = L2_talon->GetMotorOutputPercent();
		double R3_motorOutput = R3_talon->GetMotorOutputPercent();
		//double R4_motorOutput = R4_talon->GetMotorOutputPercent();
		/* prepare line to print */
		_sb.append("\tout:");
		_sb.append(std::to_string(L1_motorOutput));
   		_sb.append(std::to_string(R3_motorOutput));

		_sb.append("\tspd:");
		_sb.append(std::to_string(L1_talon->GetSelectedSensorVelocity(kPIDLoopIdx)));
		_sb.append(std::to_string(R3_talon->GetSelectedSensorVelocity(kPIDLoopIdx)));

		/* while button1 is held down, closed-loop on target velocity */
		if (_joy->GetRawButton(1)) {
        	/* Speed mode */
			/* Convert 500 RPM to units / 100ms.
			 * 4096 Units/Rev * 500 RPM / 600 100ms/min in either direction:
			 * velocity setpoint is in units/100ms
			 */
			double targetVelocity_UnitsPer100ms = leftYstick * 500.0 * 4096 / 600;
			/* 500 RPM in either direction */
        	L1_talon->Set(ControlMode::Velocity, targetVelocity_UnitsPer100ms); 
			R3_talon->Set(ControlMode::Velocity, targetVelocity_UnitsPer100ms);

			/* append more signals to print when in speed mode. */
			_sb.append("\terrNative:");
			_sb.append(std::to_string(L1_talon->GetClosedLoopError(kPIDLoopIdx)));
			_sb.append(std::to_string(R3_talon->GetClosedLoopError(kPIDLoopIdx)));
			_sb.append("\ttrg:");
			_sb.append(std::to_string(targetVelocity_UnitsPer100ms));
        } else {
			/* Percent voltage mode */
			L1_talon->Set(ControlMode::PercentOutput, leftYstick);
			R3_talon->Set(ControlMode::PercentOutput, leftYstick);
		}
		/* print every ten loops, printing too much too fast is generally bad for performance */
		if (++_loops >= 10) {
			_loops = 0;
			printf("%s\n",_sb.c_str());
		}
		_sb.clear();
	}
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
