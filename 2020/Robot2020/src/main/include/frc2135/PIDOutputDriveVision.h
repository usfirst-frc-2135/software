/*
 * PIDOutputDriveVision.h
 *
 *  Created on: Jan 25, 2020
 */

#pragma once

#include <frc/PIDOutput.h>
#include <frc/drive/DifferentialDrive.h>

class PIDOutputDriveVision: public frc::PIDOutput {

private:
	std::shared_ptr<frc::DifferentialDrive> m_robotDrive;
	double m_visionAngle;
    double m_turnAngle;

public:
	PIDOutputDriveVision(std::shared_ptr<frc::DifferentialDrive> robotDrive);
	virtual ~PIDOutputDriveVision();
	void PIDWrite(double output);
	void SetTurnAngle(double angle);
};
