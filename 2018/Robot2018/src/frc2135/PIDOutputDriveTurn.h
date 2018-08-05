/*
 * PIDOutputDriveTurn.h
 *
 *  Created on: Jan 28, 2018
 *      Author: Administrator
 */

#ifndef SRC_FRC2135_PIDOUTPUTDRIVETURN_H_
#define SRC_FRC2135_PIDOUTPUTDRIVETURN_H_

#include "WPILib.h" // To use the WPI Library
#include "../RobotDefaults.h" // To get values from Robot Defaults

class PIDOutputDriveTurn: public frc::PIDOutput {
private:
	std::shared_ptr<DifferentialDrive> m_robotDrive; // Uses robotDrive motors

public:
	PIDOutputDriveTurn(std::shared_ptr<DifferentialDrive> robotDrive);
	virtual ~PIDOutputDriveTurn(void);
	void PIDWrite(double output);
};

#endif /* SRC_FRC2135_PIDOUTPUTDRIVETURN_H_ */
