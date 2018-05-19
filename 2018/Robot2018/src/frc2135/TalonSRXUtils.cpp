/*
 * TalonSRXUtils.cpp
 *
 *  Created on: May 14, 2018
 *      Author: PHS_User
 */

#include <frc2135/TalonSRXUtils.h>
#include <chrono>

namespace frc2135 {

TalonSRXUtils::TalonSRXUtils() {
	// TODO Auto-generated constructor stub

}

TalonSRXUtils::~TalonSRXUtils() {
	// TODO Auto-generated destructor stub
}

ErrorCode TalonSRXUtils::TalonSRXCheck(std::shared_ptr<WPI_TalonSRX> talonSRX, const char *subsystem, const char *name) {
	int					i;
	int					deviceID = 0;
	int					fwVersion = 0;
	bool				talonValid = false;
	ErrorCode			error = OKAY;

	// Display Talon SRX firmware versions
	deviceID = talonSRX->GetDeviceID();
	if ((error = talonSRX->GetLastError()) != OKAY) {
		std::printf("2135: ERROR: %s Motor %s GetDeviceID error - %d\n", subsystem, name, error);
		return error;
	}

	for (i = 0; i < 5; i++) {
		fwVersion = talonSRX->GetFirmwareVersion();
		if ((error = talonSRX->GetLastError()) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s GetFirmwareVersion error - %d\n", subsystem, name, error);
			return error;
		}
		if (fwVersion == m_reqVersion) {
			talonValid = true;
			break;
		}
		else {
			std::printf("2135: WARNING: %s Motor %s Incorrect FW version %d.%d expected %d.%d\n",
					subsystem, name, fwVersion/256, fwVersion%256, m_reqVersion/256, m_reqVersion%256);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}

	if ((error = talonSRX->ConfigOpenloopRamp(0.0, m_timeout)) != OKAY) {
		std::printf("2135: ERROR: %s Motor %s ConfigOpenloopRamp error - %d\n", subsystem, name, error);
	}
	talonSRX->ConfigClosedloopRamp(0.0, m_timeout);
	talonSRX->ConfigPeakOutputForward(1.0, m_timeout);
	talonSRX->ConfigPeakOutputReverse(-1.0, m_timeout);
	talonSRX->ConfigNominalOutputForward(0.0, m_timeout);
	talonSRX->ConfigNominalOutputReverse(0.0, m_timeout);
	talonSRX->ConfigNeutralDeadband(0.04, m_timeout);
	talonSRX->ConfigVoltageCompSaturation(0.0, m_timeout);
	talonSRX->ConfigVoltageMeasurementFilter(32, m_timeout);
	talonSRX->ConfigSelectedFeedbackSensor(QuadEncoder, m_pidIndex, m_timeout);
	talonSRX->ConfigSelectedFeedbackCoefficient(1.0, m_pidIndex, m_timeout);
	talonSRX->ConfigRemoteFeedbackFilter(0, RemoteSensorSource::RemoteSensorSource_Off, 0, m_timeout);
	talonSRX->ConfigRemoteFeedbackFilter(0, RemoteSensorSource::RemoteSensorSource_Off, 1, m_timeout);
	talonSRX->ConfigSensorTerm(SensorTerm::SensorTerm_Sum0, QuadEncoder, m_timeout);
	talonSRX->ConfigSensorTerm(SensorTerm::SensorTerm_Sum1, QuadEncoder, m_timeout);
	talonSRX->ConfigSensorTerm(SensorTerm::SensorTerm_Diff0, QuadEncoder, m_timeout);
	talonSRX->ConfigSensorTerm(SensorTerm::SensorTerm_Diff1, QuadEncoder, m_timeout);
	talonSRX->ConfigVelocityMeasurementPeriod(VelocityMeasPeriod::Period_100Ms, m_timeout);
	talonSRX->ConfigVelocityMeasurementWindow(64, m_timeout);
	talonSRX->ConfigForwardLimitSwitchSource(LimitSwitchSource_Deactivated , LimitSwitchNormal_NormallyOpen, m_timeout);
	talonSRX->ConfigReverseLimitSwitchSource(LimitSwitchSource_Deactivated , LimitSwitchNormal_NormallyOpen, m_timeout);
	talonSRX->ConfigForwardSoftLimitThreshold(0, m_timeout);
	talonSRX->ConfigReverseSoftLimitThreshold(0, m_timeout);
	talonSRX->ConfigForwardSoftLimitEnable(false, m_timeout);
	talonSRX->ConfigReverseSoftLimitEnable(false, m_timeout);
	talonSRX->Config_kP(m_slotIndex, 0.0, m_timeout);
	talonSRX->Config_kI(m_slotIndex, 0.0, m_timeout);
	talonSRX->Config_kD(m_slotIndex, 0.0, m_timeout);
	talonSRX->Config_kF(m_slotIndex, 0.0, m_timeout);
	talonSRX->Config_IntegralZone(m_slotIndex, 0, m_timeout);
	talonSRX->ConfigAllowableClosedloopError(m_slotIndex, 0, m_timeout);
	talonSRX->ConfigMaxIntegralAccumulator(m_slotIndex, 0.0, m_timeout);
	talonSRX->ConfigClosedLoopPeakOutput(m_slotIndex, 1.0, m_timeout);
	talonSRX->ConfigClosedLoopPeriod(m_slotIndex, 1, m_timeout);
	talonSRX->ConfigAuxPIDPolarity(false, m_timeout);
	talonSRX->ConfigMotionCruiseVelocity(0, m_timeout);
	talonSRX->ConfigMotionAcceleration(0, m_timeout);
	talonSRX->ConfigMotionProfileTrajectoryPeriod(0, m_timeout);
	talonSRX->ConfigSetCustomParam(0, 0, m_timeout);
	talonSRX->ConfigSetCustomParam(0, 1, m_timeout);
	talonSRX->ConfigPeakCurrentLimit(0, m_timeout);
	talonSRX->ConfigPeakCurrentDuration(0, m_timeout);
	talonSRX->ConfigContinuousCurrentLimit(0, m_timeout);

	if (talonValid) {
		std::printf("2135: %s Motor %s ID %d ver %d.%d is RESPONSIVE and INITIALIZED (error %d)\n",
				subsystem, name, deviceID, fwVersion/256, fwVersion&0xff, error);
	}
	else {
		std::printf("2135: ERROR: %s Motor %s ID %d ver %d.%d is UNRESPONSIVE, (error %d)\n",
				subsystem, name, deviceID, fwVersion/256, fwVersion&0xff, error);
	}

	return error;
}

} /* namespace frc2135 */
