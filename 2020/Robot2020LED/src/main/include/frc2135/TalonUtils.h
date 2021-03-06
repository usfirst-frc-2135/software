/*
 * TalonUtils.h
 *
 *  Created on: Jan 14, 2020
 *      Author: PHS_User
 */

#pragma once

#include <ctre/Phoenix.h>

namespace frc2135 {

class TalonUtils {
public:
	TalonUtils();
	virtual ~TalonUtils();
	static bool TalonCheck(std::shared_ptr<WPI_BaseMotorController> talon, const char *subsystem, const char *name);
	static void TalonFaultDump(const char *talonName, std::shared_ptr<WPI_BaseMotorController> talonPtr);

private:
	static const int		m_slotIndex = 0;				// Motor controller profile slot index
	static const int		m_pidIndex = 0; 				// PID Slot index for sensors
	static const int		m_timeout = 30;					// CAN timeout in msec to wait for response
	static const int		m_retries = 4;					// Number of version check attempts

	static const int		m_reqVersion = ((20*256)+0);	// Talon version is 20.0
};

} /* namespace frc2135 */

