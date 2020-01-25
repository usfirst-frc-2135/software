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

#include"frc/Joystick.h"
#include "frc/TimedRobot.h"
#include <frc/commands/Subsystem.h>
#include "Drivetrain.h"
#include "Constants.h"

using namespace frc;

class Robot: public frc::TimedRobot {
public:

	Joystick *_joy;
	std::string _sb;
	int _loops = 0;
	Drivetrain *_drivetrain;
	
Robot(){

	_joy = new Joystick(0);
	_sb ="";
	_loops = 0;
	_drivetrain = new Drivetrain();
	RobotInit();
};

	void TeleopPeriodic() {
		/* get gamepad axis */
		double leftYstick = _joy->GetY();
		double L1_motorOutput = _L1talon->GetMotorOutputPercent();
		//double L2_motorOutput = _L2talon->GetMotorOutputPercent();
		double R3_motorOutput = _R3talon->GetMotorOutputPercent();
		//double R4_motorOutput = _R4talon->GetMotorOutputPercent();
		/* prepare line to print */
		_sb.append("\tout:");
		_sb.append(std::to_string(L1_motorOutput));
   		_sb.append(std::to_string(R3_motorOutput));

		_sb.append("\tspd:");
		_sb.append(std::to_string(_L1talon->GetSelectedSensorVelocity(kPIDLoopIdx)));
		_sb.append(std::to_string(_R3talon->GetSelectedSensorVelocity(kPIDLoopIdx)));

		/* while button1 is held down, closed-loop on target velocity */
		if (_joy->GetRawButton(1)) {
        	/* Speed mode */
			/* Convert 500 RPM to units / 100ms.
			 * 4096 Units/Rev * 500 RPM / 600 100ms/min in either direction:
			 * velocity setpoint is in units/100ms
			 */
			double targetVelocity_UnitsPer100ms = leftYstick * 500.0 * 4096 / 600;
			/* 500 RPM in either direction */
        	_L1talon->Set(ControlMode::Velocity, targetVelocity_UnitsPer100ms); 
			_R3talon->Set(ControlMode::Velocity, targetVelocity_UnitsPer100ms);

			/* append more signals to print when in speed mode. */
			_sb.append("\terrNative:");
			_sb.append(std::to_string(_L1talon->GetClosedLoopError(kPIDLoopIdx)));
			_sb.append(std::to_string(_R3talon->GetClosedLoopError(kPIDLoopIdx)));
			_sb.append("\ttrg:");
			_sb.append(std::to_string(targetVelocity_UnitsPer100ms));
        } else {
			/* Percent voltage mode */
			_L1talon->Set(ControlMode::PercentOutput, leftYstick);
			_R3talon->Set(ControlMode::PercentOutput, leftYstick);
		}
		/* print every ten loops, printing too much too fast is generally bad for performance */
		if (++_loops >= 10) {
			_loops = 0;
			printf("%s\n",_sb.c_str());
		}
		_sb.clear();
	};
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
