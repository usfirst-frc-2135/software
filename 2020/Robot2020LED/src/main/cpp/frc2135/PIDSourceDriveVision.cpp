/*
 * PIDSourceDriveVision.cpp
 *
 *  Created on: Jan 25, 2020
 */

#include "frc2135/PIDSourceDriveVision.h"
#include "Robot.h"

PIDSourceDriveVision::PIDSourceDriveVision() {
	m_angle = 0.0;
}

PIDSourceDriveVision::~PIDSourceDriveVision() {
}

double PIDSourceDriveVision::PIDGet(void) {
	double currAngle = 0.0;

	currAngle = Robot::vision->GetHorzOffset();
    return currAngle;
}

void PIDSourceDriveVision::SetTurnAngle(double angle) {
	m_angle = angle;
}
