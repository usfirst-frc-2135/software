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
	void SetTurnAngle(double angle);
	void PIDWrite(double output);
	virtual ~PIDOutputDriveVision();
};

#endif /* SRC_SUBSYSTEMS_PIDOUTPUTDRIVEVISION_H_ */
