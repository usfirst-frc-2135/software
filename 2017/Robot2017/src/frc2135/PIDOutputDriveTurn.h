/*
 * PIDOutputDriveTurn.h
 *
 *  Created on: Nov 22, 2017
 *      Author: jeffmullins
 */

#ifndef SRC_SUBSYSTEMS_PIDOUTPUTDRIVETURN_H_
#define SRC_SUBSYSTEMS_PIDOUTPUTDRIVETURN_H_

#include "WPILib.h"
#include "CANTalon.h"
#include "../RobotDefaults.h"

class PIDOutputDriveTurn: public frc::PIDOutput {
private:
	std::shared_ptr<RobotDrive> m_robotDrive;

public:
	PIDOutputDriveTurn(std::shared_ptr<RobotDrive> rDrive);
	virtual ~PIDOutputDriveTurn();
	void PIDWrite(double output);
};

#endif /* SRC_SUBSYSTEMS_PIDOUTPUTDRIVETURN_H_ */
