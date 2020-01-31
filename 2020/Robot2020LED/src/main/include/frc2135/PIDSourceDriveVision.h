/*
 * PIDSourceDriveVision.h
 *
 *  Created on: Jan 25, 2020
 */

#pragma once 

#include <frc/PIDSource.h>

class PIDSourceDriveVision: public frc::PIDSource {
private:
	double	m_angle;
    // double  m_visionAngle; 

public:
	PIDSourceDriveVision();
	virtual ~PIDSourceDriveVision();
    double PIDGet(void);
	void SetTurnAngle(double angle);
};