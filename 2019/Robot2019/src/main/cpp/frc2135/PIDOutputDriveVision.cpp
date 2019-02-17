/*
 * PIDOutputDriveVision.cpp
 *
 *  Created on: Nov 22, 2017
 *      Author: jeffmullins
 */
#include "Robot.h"
#include "RobotDefaults.h"
#include "frc2135/PIDOutputDriveVision.h"

// Drive Vision output class derived from PID Output
//	Used to drive toward a heading for a specified distance

PIDOutputDriveVision::PIDOutputDriveVision(std::shared_ptr<frc::DifferentialDrive> robotDrive) {
	m_robotDrive = robotDrive;

	m_turnAngle = 0.0;

	m_visionAngle = frc::SmartDashboard::GetNumber(CAM_TURNANGLE, CAM_TURNANGLE_D);
	std::printf("2135: CameraVisionAngle: %f degrees\n", m_visionAngle);
	m_visionDistance = frc::SmartDashboard::GetNumber(CAM_DISTANCE, CAM_DISTANCE_D);
	std::printf("2135: CameraVisionAngle: %f inches\n", m_visionDistance);
}

PIDOutputDriveVision::~PIDOutputDriveVision() {
}

void PIDOutputDriveVision::PIDWrite(double output) {
	double 			m_offset;
	const double 	kP_turn = (0.18 / 21.0);	// turn power difference (0.18) to turn 21 degrees

	m_offset = -(Robot::drivetrain->GetAngle() - m_turnAngle) * kP_turn;
	m_robotDrive->TankDrive(-(output + m_offset), output - m_offset);

	std::printf("2135: Left %f Right %f\n", -(output + m_offset), output - m_offset);
}

void PIDOutputDriveVision::SetTurnAngle(double angle) {
	m_turnAngle = angle;
}
