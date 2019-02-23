/*
 * TalonSRXUtils.h
 *
 *  Created on: May 14, 2018
 *      Author: PHS_User
 */

#include "frc/WPILib.h"
#include "ctre/Phoenix.h"

#ifndef SRC_FRC2135_TALONSRXUTILS_H_
#define SRC_FRC2135_TALONSRXUTILS_H_

namespace frc2135 {

class TalonSRXUtils {
public:
	TalonSRXUtils();
	virtual ~TalonSRXUtils();
	static bool TalonSRXCheck(std::shared_ptr<WPI_TalonSRX> talonSRX, const char *subsystem, const char *name);
	static void TalonSRXFaultDump(const char *talonName, std::shared_ptr<WPI_TalonSRX> talonPtr);

private:
	static const int		m_slotIndex = 0;				// Motor controller profile slot index
	static const int		m_pidIndex = 0; 				// PID Slot index for sensors
	static const int		m_timeout = 30;					// CAN timeout in msec to wait for response
	static const int		m_retries = 4;					// Number of version check attempts

	static const int		m_reqVersion = ((4*256)+17);		// Talon SRX version is 4.17
};

} /* namespace frc2135 */

#endif /* SRC_FRC2135_TALONSRXUTILS_H_ */
