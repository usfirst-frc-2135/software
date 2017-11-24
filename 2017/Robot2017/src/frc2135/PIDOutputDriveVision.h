/*
 * PIDOutputDriveVision.h
 *
 *  Created on: Nov 22, 2017
 *      Author: jeffmullins
 */

#ifndef SRC_SUBSYSTEMS_PIDOUTPUTDRIVEVISION_H_
#define SRC_SUBSYSTEMS_PIDOUTPUTDRIVEVISION_H_

#include "WPILib.h"
#include "CANTalon.h"
#include "../RobotDefaults.h"

class PIDOutputDriveVision: public frc::PIDOutput {
private:
	std::shared_ptr<RobotDrive> m_robotDrive;
	double m_visionAngle;
	double m_visionDistance;
	double m_turnAngle;

public:
	PIDOutputDriveVision(std::shared_ptr<RobotDrive> drive);
	virtual ~PIDOutputDriveVision();
	void PIDWrite(double output);
	void SetTurnAngle(double angle);
};

#endif /* SRC_SUBSYSTEMS_PIDOUTPUTDRIVEVISION_H_ */
