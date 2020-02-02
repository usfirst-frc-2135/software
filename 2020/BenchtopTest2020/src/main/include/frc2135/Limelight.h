/*
 * Limelight.h
 *
 *  Created on: Feb 2, 2019
 */

#include <frc/smartdashboard/Smartdashboard.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>

#ifndef LIMELIGHT_H
#define LIMELIGHT_H

namespace frc2135 {

class Limelight {
public:
	Limelight();
	virtual ~Limelight();
	static void ReadData();
	static void SetStream();

};

} /* namespace frc2135 */

#endif
