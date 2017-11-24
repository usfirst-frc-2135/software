/*
 * PIDSourceDriveVision.h
 *
 *  Created on: Nov 23, 2017
 *      Author: jeffmullins
 */

#ifndef SRC_SUBSYSTEMS_PIDSOURCEDRIVEVISION_H_
#define SRC_SUBSYSTEMS_PIDSOURCEDRIVEVISION_H_

#include "WPILib.h"
#include "CANTalon.h"
#include "../RobotDefaults.h"

class PIDSourceDriveVision: public frc::PIDSource {
private:
	double	m_angle;
	static const int numSamples = 8;
	double m_angleBuffer[numSamples];
	int m_curSample = 0;
	double m_totSamples = 0;
#ifdef CRUSH_SETTINGS
	const double				EncoderDirection = 1.0;		// Crush encoders read positive values
#else
	const double				EncoderDirection = -1.0;	// Brush encoders read negative values
#endif

public:
	PIDSourceDriveVision();
	virtual ~PIDSourceDriveVision();
	double PIDGet(void);
	void SetTurnAngle(double angle);
};

#endif /* SRC_SUBSYSTEMS_PIDSOURCEDRIVEVISION_H_ */
