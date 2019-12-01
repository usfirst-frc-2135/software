/*
 * PIDSourceDriveTurn.h
 *
 *  Created on: Feb 19, 2019
 */

#ifndef SRC_SUBSYSTEMS_PIDSOURCEDRIVETURN_H_
#define SRC_SUBSYSTEMS_PIDSOURCEDRIVETURN_H_

#include "RobotDefaults.h"
#include "frc/PIDSource.h"
#include "frc/PIDOutput.h"
#include "frc/PIDController.h"

class PIDSourceDriveTurn: public frc::PIDSource {
private:
  double          m_angle;
  const double				EncoderDirection = -1.0;		// TODO: Change based on sign of robot encoder values

public:
	PIDSourceDriveTurn();
	virtual ~PIDSourceDriveTurn();
  double PIDGet(void);
	void SetTurnAngle(double angle);
};

#endif /* SRC_SUBSYSTEMS_PIDSOURCEDRIVETURN_H_ */
