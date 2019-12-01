/*
 * PIDSourceDriveVision.cpp
 *
 *  Created on: Nov 23, 2017
 *      Author: jeffmullins
 */

#include "Robot.h"
#include "RobotDefaults.h"
#include "frc2135/PIDSourceDriveVision.h"

//  Drive Vision source class derived from PID Source
//	Used to drive toward a heading for a specified distance

PIDSourceDriveVision::PIDSourceDriveVision() {
	m_angle = 0.0;
}

PIDSourceDriveVision::~PIDSourceDriveVision() {
}

double PIDSourceDriveVision::PIDGet(void) {
	double encPosition = 0.0;

	// Get the current encoder positions from Talon
	if (m_angle < 0.0)
		encPosition = (double)Robot::drivetrain->GetEncoderPosition(3);
//		encPosition = (double)RobotMap::chassisMotorR3->GetSelectedSensorPosition(0);
	else
		encPosition = (double)Robot::drivetrain->GetEncoderPosition(1);
//		encPosition = -(double)RobotMap::chassisMotorL1->GetSelectedSensorPosition(0);

#if 0	// If averaging is needed leave this in
	int i;

	// Limit the gyro input to a valid range
	curAngle = fmin(curAngle, 25.0);
	curAngle = fmax(curAngle, -25.0);

	// Store in the gyro angle buffer
	m_angleBuffer[m_curSample++] = curAngle;
	if (m_curSample >= numSamples)
		m_curSample = 0;
	if (m_totSamples < m_totSamples)
		m_totSamples++;

	// Reuse curAngle to average the samples over total samples in buffer
	curAngle = 0.0;
	for (i = 0; i < m_totSamples; i++) {
		curAngle += m_angleBuffer[i];
	}
	curAngle = curAngle / m_totSamples;
#endif

	return encPosition * EncoderDirection;
}

void PIDSourceDriveVision::SetTurnAngle(double angle) {
	m_angle = angle;
}
