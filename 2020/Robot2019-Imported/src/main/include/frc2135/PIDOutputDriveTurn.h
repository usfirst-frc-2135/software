/*
 * PIDOutputDriveTurn.h
 *
 *  Created on: Nov 22, 2017
 *      Author: jeffmullins
 */

#ifndef SRC_SUBSYSTEMS_PIDOUTPUTDRIVETURN_H_
#define SRC_SUBSYSTEMS_PIDOUTPUTDRIVETURN_H_

#include <frc/drive/DifferentialDrive.h>

#include "frc/PIDSource.h"
#include "frc/PIDOutput.h"
#include "frc/PIDController.h"

#include "RobotDefaults.h"

class PIDOutputDriveTurn: public frc::PIDOutput {
private:
	std::shared_ptr<frc::DifferentialDrive> m_robotDrive;

public:
	PIDOutputDriveTurn(std::shared_ptr<frc::DifferentialDrive> rDrive);
	virtual ~PIDOutputDriveTurn();
	void PIDWrite(double output);
};

#endif /* SRC_SUBSYSTEMS_PIDOUTPUTDRIVETURN_H_ */
