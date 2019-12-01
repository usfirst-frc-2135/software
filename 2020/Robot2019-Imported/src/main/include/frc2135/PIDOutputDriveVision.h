/*
 * PIDOutputDriveVision.h
 *
 *  Created on: Nov 22, 2017
 *      Author: jeffmullins
 */

#ifndef SRC_SUBSYSTEMS_PIDOUTPUTDRIVEVISION_H_
#define SRC_SUBSYSTEMS_PIDOUTPUTDRIVEVISION_H_

#include "RobotDefaults.h"
#include "frc/PIDSource.h"
#include "frc/PIDOutput.h"
#include "frc/PIDController.h"

class PIDOutputDriveVision: public frc::PIDOutput {
private:
	std::shared_ptr<frc::DifferentialDrive> m_robotDrive;
	double m_visionAngle;
	double m_visionDistance;
	double m_turnAngle;

public:
	PIDOutputDriveVision(std::shared_ptr<frc::DifferentialDrive> drive);
	virtual ~PIDOutputDriveVision();
	void PIDWrite(double output);
	void SetTurnAngle(double angle);
};

#endif /* SRC_SUBSYSTEMS_PIDOUTPUTDRIVEVISION_H_ */
