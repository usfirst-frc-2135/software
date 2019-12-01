/*
 * PIDOutputDriveTurn.cpp
 *
 *  Created on: Nov 22, 2017
 *      Author: jeffmullins
 */

#include "RobotDefaults.h"
#include "frc2135/PIDOutputDriveTurn.h"

// Drive Turn output class derived from PID Output
//	Used to turn to a specified angle

PIDOutputDriveTurn::PIDOutputDriveTurn(std::shared_ptr<frc::DifferentialDrive> robotDrive) {
	m_robotDrive = robotDrive;
}

PIDOutputDriveTurn::~PIDOutputDriveTurn() {
}

void PIDOutputDriveTurn::PIDWrite(double output) {
	if (output > 0.0) {
		m_robotDrive->TankDrive(0.0, -output);
	}
	else {
		m_robotDrive->TankDrive(output, 0.0);
	}
}
