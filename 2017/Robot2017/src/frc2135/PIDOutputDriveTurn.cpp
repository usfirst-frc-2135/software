/*
 * PIDOutputDriveTurn.cpp
 *
 *  Created on: Nov 22, 2017
 *      Author: jeffmullins
 */

#include "PIDOutputDriveTurn.h"
#include "../RobotMap.h"

// Drive Turn output class derived from PID Output
//	Used to turn to a specified angle

PIDOutputDriveTurn::PIDOutputDriveTurn(std::shared_ptr<RobotDrive> robotDrive) {
	m_robotDrive = robotDrive;
}

PIDOutputDriveTurn::~PIDOutputDriveTurn() {
}

void PIDOutputDriveTurn::PIDWrite(double output) {
	if (output > 0.0) {
		m_robotDrive->SetLeftRightMotorOutputs(0.0, output);

		// TODO: Comment out after tuning -- place one in PID stop method to show result
		SmartDashboard::PutNumber(CHS_TURNPID_OUT_L, 0.0);
		SmartDashboard::PutNumber(CHS_TURNPID_OUT_R, output);
	}
	else {
		m_robotDrive->SetLeftRightMotorOutputs(-output, 0.0);

		// TODO: Comment out after tuning -- place one in PID stop method to show result
		SmartDashboard::PutNumber(CHS_TURNPID_OUT_L, -output);
		SmartDashboard::PutNumber(CHS_TURNPID_OUT_R, 0.0);
	}
}
