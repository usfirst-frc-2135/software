/*
 * TalonFXUtils.h
 *
 *  Created on: Jan 14, 2020
 *      Author: PHS_User
 */

#include <ctre/Phoenix.h>

#ifndef SRC_FRC2135_TALONFXUTILS_H_
#define SRC_FRC2135_TALONFXUTILS_H_

namespace frc2135 {

class TalonFXUtils {
public:
	TalonFXUtils();
	virtual ~TalonFXUtils();
	static bool TalonFXCheck(std::shared_ptr<WPI_TalonFX> talonFX, const char *subsystem, const char *name);
	static void TalonFXFaultDump(const char *talonName, std::shared_ptr<WPI_TalonFX> talonPtr);

private:
	static const int		m_slotIndex = 0;				// Motor controller profile slot index
	static const int		m_pidIndex = 0; 				// PID Slot index for sensors
	static const int		m_timeout = 30;					// CAN timeout in msec to wait for response
	static const int		m_retries = 4;					// Number of version check attempts

	static const int		m_reqVersion = ((20*256)+0);		// Talon FX version is 20.0
};

} /* namespace frc2135 */

#endif /* SRC_FRC2135_TALONFXUTILS_H_ */
