/*
 * PIDOutputDriveTurn.h
 *
 *  Created on: Jan 28, 2018
 *      Author: Administrator
 */

#ifndef SRC_FRC2135_PIDOUTPUTDRIVETURN_H_
#define SRC_FRC2135_PIDOUTPUTDRIVETURN_H_

#include "frc/WPILib.h" // To use the WPI Library

class PIDOutputDriveTurn: public frc::PIDOutput {
private:
	std::shared_ptr<frc::DifferentialDrive> m_robotDrive; // Uses robotDrive motors

public:
	PIDOutputDriveTurn(std::shared_ptr<frc::DifferentialDrive> robotDrive);
	virtual ~PIDOutputDriveTurn(void);
	void PIDWrite(double output);
};

#endif /* SRC_FRC2135_PIDOUTPUTDRIVETURN_H_ */
