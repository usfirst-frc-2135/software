/*
 * PIDOutputDriveTurn.cpp
 *
 *  Created on: Jan 28, 2018
 *      Author: Administrator
 */

#include "frc2135/PIDOutputDriveTurn.h" // Link .h file with .cpp file because this is not autogenerated and will not do it automatically

// Class from the PID Output
PIDOutputDriveTurn::PIDOutputDriveTurn(std::shared_ptr<frc::DifferentialDrive> robotDrive) {
	m_robotDrive = robotDrive; // So the PID uses the Talons in the drive motor
}

PIDOutputDriveTurn::~PIDOutputDriveTurn(void) {
}

void PIDOutputDriveTurn::PIDWrite(double output) {
	// Send right/left motor outputs and disable squaring of the TankDrive input values
	m_robotDrive->TankDrive(output, -output, false);
}

