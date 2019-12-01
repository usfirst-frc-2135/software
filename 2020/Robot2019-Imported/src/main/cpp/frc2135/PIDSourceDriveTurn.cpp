/*
 * PIDSourceDriveTurn.cpp
 *
 *  Created on: Feb 19, 2019
 */

#include "Robot.h"
#include "RobotDefaults.h"
#include "frc2135/PIDSourceDriveTurn.h"

//  Drive Turn source class derived from PID Source
//	Used to turn to a specified angle

PIDSourceDriveTurn::PIDSourceDriveTurn() {
	m_angle = 0.0;
}

PIDSourceDriveTurn::~PIDSourceDriveTurn() {
}

double PIDSourceDriveTurn::PIDGet(void) {
	double encPosition = 0.0;

	// Get the current encoder positions from Talon
	if (m_angle < 0.0)
		encPosition = (double)Robot::drivetrain->GetEncoderPosition(3);
	else
		encPosition = (double)Robot::drivetrain->GetEncoderPosition(1);

	return encPosition * EncoderDirection;
}

void PIDSourceDriveTurn::SetTurnAngle(double angle) {
	m_angle = angle;
}
