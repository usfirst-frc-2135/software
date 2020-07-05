/*
 * PIDOutputDriveVision.cpp
 *
 *  Created on: Jan 25, 2020
 */

#include "frc2135/PIDOutputDriveVision.h"
#include "Robot.h"

PIDOutputDriveVision::PIDOutputDriveVision(std::shared_ptr<frc::DifferentialDrive> robotDrive)
{
	m_robotDrive = robotDrive;
}

PIDOutputDriveVision::~PIDOutputDriveVision()
{

}

void PIDOutputDriveVision::PIDWrite(double output)
{
	double 			m_offset;
	const double 	Kp_turn = (0.18 / 21.0);	// TODO: determine turn power difference to turn a certain number of degrees

	m_visionAngle = Robot::vision->GetHorzOffset();
	m_offset = m_visionAngle * Kp_turn;
	m_robotDrive->TankDrive(-(output + m_offset), output + m_offset);

	std::printf("2135: Left %f Right %f\n", -(output + m_offset), output - m_offset);
}

void PIDOutputDriveVision::SetTurnAngle(double angle)
{
	m_turnAngle = angle;
}
