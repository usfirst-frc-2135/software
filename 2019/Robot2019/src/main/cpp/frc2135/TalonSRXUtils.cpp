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
	// Auto-generated constructor stub
}

TalonSRXUtils::~TalonSRXUtils() {
	// Auto-generated destructor stub
}

bool TalonSRXUtils::TalonSRXCheck(std::shared_ptr<WPI_TalonSRX> talonSRX, const char *subsystem, const char *name) {
	int					i;
	int					deviceID = 0;
	int					fwVersion = 0;
	bool				talonValid = false;
	ErrorCode			error = OKAY;

	// Configure subsystem and component name
    talonSRX->SetName(subsystem, name);
   	std::printf("2135: TalonSRX Subsystem %s Name %s\n", talonSRX->GetSubsystem().c_str(), talonSRX->GetName().c_str());

    // Display Talon SRX firmware versions
	deviceID = talonSRX->GetDeviceID();
	if ((error = talonSRX->GetLastError()) != OKAY) {
		std::printf("2135: ERROR: %s Motor %s GetDeviceID error - %d\n", subsystem, name, error);
		return error;
	}

	for (i = 0; i < m_retries; i++) {
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

	if (talonValid) {
		int		i;

		// Initialize ramp rates, peak and nominal outputs
		if ((error = talonSRX->ConfigOpenloopRamp(0.0, m_timeout)) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s ConfigOpenloopRamp error - %d\n", subsystem, name, error);
		}
		if ((error = talonSRX->ConfigClosedloopRamp(0.0, m_timeout)) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s ConfigOpenloopRamp error - %d\n", subsystem, name, error);
		}

		if ((error = talonSRX->ConfigPeakOutputForward(1.0, m_timeout)) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s ConfigPeakOutputForward error - %d\n", subsystem, name, error);
		}
		if ((error = talonSRX->ConfigPeakOutputReverse(-1.0, m_timeout)) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s ConfigPeakOutputReverse error - %d\n", subsystem, name, error);
		}

		if ((error = talonSRX->ConfigNominalOutputForward(0.0, m_timeout)) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s ConfigNominalOutputForward error - %d\n", subsystem, name, error);
		}
		if ((error = talonSRX->ConfigNominalOutputReverse(0.0, m_timeout)) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s ConfigNominalOutputReverse error - %d\n", subsystem, name, error);
		}

		// Initialize neutral deadband back to default
		if ((error = talonSRX->ConfigNeutralDeadband(0.04, m_timeout)) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s ConfigNeutralDeadband error - %d\n", subsystem, name, error);
		}

		// Initialize voltage compensation filter
		if ((error = talonSRX->ConfigVoltageCompSaturation(0.0, m_timeout)) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s ConfigVoltageCompSaturation error - %d\n", subsystem, name, error);
		}
		if ((error = talonSRX->ConfigVoltageMeasurementFilter(32, m_timeout)) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s ConfigVoltageMeasurementFilter error - %d\n", subsystem, name, error);
		}

		// Initialize feedback sensor settings
		if ((error = talonSRX->ConfigSelectedFeedbackSensor(QuadEncoder, m_pidIndex, m_timeout)) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s ConfigSelectedFeedbackSensor error - %d\n", subsystem, name, error);
		}
		if ((error = talonSRX->ConfigSelectedFeedbackCoefficient(1.0, m_pidIndex, m_timeout)) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s ConfigSelectedFeedbackCoefficient error - %d\n", subsystem, name, error);
		}

		//	Initialize remote sensors
		for (i = 0; i < 2; i++) {
			if ((error = talonSRX->ConfigRemoteFeedbackFilter(0, RemoteSensorSource::RemoteSensorSource_Off, i, m_timeout)) != OKAY) {
				std::printf("2135: ERROR: %s Motor %s ConfigRemoteFeedbackFilter (%d)error - %d\n", subsystem, name, i, error);
			}
		}

		if ((error = talonSRX->ConfigSensorTerm(SensorTerm::SensorTerm_Sum0, QuadEncoder, m_timeout)) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s ConfigSensorTerm error - %d\n", subsystem, name, error);
		}
		if ((error = talonSRX->ConfigSensorTerm(SensorTerm::SensorTerm_Sum1, QuadEncoder, m_timeout)) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s ConfigSensorTerm error - %d\n", subsystem, name, error);
		}
		if ((error = talonSRX->ConfigSensorTerm(SensorTerm::SensorTerm_Diff0, QuadEncoder, m_timeout)) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s ConfigSensorTerm error - %d\n", subsystem, name, error);
		}
		if ((error = talonSRX->ConfigSensorTerm(SensorTerm::SensorTerm_Diff1, QuadEncoder, m_timeout)) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s ConfigSensorTerm error - %d\n", subsystem, name, error);
		}

		if ((error = talonSRX->ConfigVelocityMeasurementPeriod(VelocityMeasPeriod::Period_100Ms, m_timeout)) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s ConfigVelocityMeasurementPeriod error - %d\n", subsystem, name, error);
		}
		if ((error = talonSRX->ConfigVelocityMeasurementWindow(64, m_timeout)) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s ConfigVelocityMeasurementWindow error - %d\n", subsystem, name, error);
		}

		// Initialize limit switch settings
		if ((error = talonSRX->ConfigForwardLimitSwitchSource(LimitSwitchSource_Deactivated , LimitSwitchNormal_NormallyOpen, m_timeout)) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s ConfigForwardLimitSwitchSource error - %d\n", subsystem, name, error);
		}
		if ((error = talonSRX->ConfigReverseLimitSwitchSource(LimitSwitchSource_Deactivated , LimitSwitchNormal_NormallyOpen, m_timeout)) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s ConfigReverseLimitSwitchSource error - %d\n", subsystem, name, error);
		}

		if ((error = talonSRX->ConfigForwardSoftLimitThreshold(0, m_timeout)) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s ConfigForwardSoftLimitThreshold error - %d\n", subsystem, name, error);
		}
		if ((error = talonSRX->ConfigReverseSoftLimitThreshold(0, m_timeout)) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s ConfigReverseSoftLimitThreshold error - %d\n", subsystem, name, error);
		}
		if ((error = talonSRX->ConfigForwardSoftLimitEnable(false, m_timeout)) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s ConfigForwardSoftLimitEnable error - %d\n", subsystem, name, error);
		}
		if ((error = talonSRX->ConfigReverseSoftLimitEnable(false, m_timeout)) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s ConfigReverseSoftLimitEnable error - %d\n", subsystem, name, error);
		}

		// Initialize PID settings for both slots
		for (i = 0; i < 2; i++) {
			if ((error = talonSRX->Config_kP(i, 0.0, m_timeout)) != OKAY) {
				std::printf("2135: ERROR: %s Motor %s Config_kP error - %d\n", subsystem, name, error);
			}
			if ((error = talonSRX->Config_kI(i, 0.0, m_timeout)) != OKAY) {
				std::printf("2135: ERROR: %s Motor %s Config_kI error - %d\n", subsystem, name, error);
			}
			if ((error = talonSRX->Config_kD(i, 0.0, m_timeout)) != OKAY) {
				std::printf("2135: ERROR: %s Motor %s Config_kD error - %d\n", subsystem, name, error);
			}
			if ((error = talonSRX->Config_kF(i, 0.0, m_timeout)) != OKAY) {
				std::printf("2135: ERROR: %s Motor %s Config_kF error - %d\n", subsystem, name, error);
			}
			if ((error = talonSRX->Config_IntegralZone(i, 0, m_timeout)) != OKAY) {
				std::printf("2135: ERROR: %s Motor %s Config_IntegralZone error - %d\n", subsystem, name, error);
			}
			if ((error = talonSRX->ConfigAllowableClosedloopError(i, 0, m_timeout)) != OKAY) {
				std::printf("2135: ERROR: %s Motor %s ConfigAllowableClosedloopError error - %d\n", subsystem, name, error);
			}
			if ((error = talonSRX->ConfigMaxIntegralAccumulator(i, 0.0, m_timeout)) != OKAY) {
				std::printf("2135: ERROR: %s Motor %s ConfigMaxIntegralAccumulator error - %d\n", subsystem, name, error);
			}

			if ((error = talonSRX->ConfigClosedLoopPeakOutput(i, 1.0, m_timeout)) != OKAY) {
				std::printf("2135: ERROR: %s Motor %s ConfigClosedLoopPeakOutput error - %d\n", subsystem, name, error);
			}
			if ((error = talonSRX->ConfigClosedLoopPeriod(i, 1, m_timeout)) != OKAY) {
				std::printf("2135: ERROR: %s Motor %s ConfigClosedLoopPeriod error - %d\n", subsystem, name, error);
			}
		}

		if ((error = talonSRX->ConfigAuxPIDPolarity(false, m_timeout)) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s ConfigAuxPIDPolarity error - %d\n", subsystem, name, error);
		}

		// Initialize motion profile settings
		if ((error = talonSRX->ConfigMotionCruiseVelocity(0, m_timeout)) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s ConfigMotionCruiseVelocity error - %d\n", subsystem, name, error);
		}
		if ((error = talonSRX->ConfigMotionAcceleration(0, m_timeout)) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s ConfigMotionAcceleration error - %d\n", subsystem, name, error);
		}
		if ((error = talonSRX->ConfigMotionProfileTrajectoryPeriod(0, m_timeout)) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s ConfigMotionProfileTrajectoryPeriod error - %d\n", subsystem, name, error);
		}

		// Initialize custom paremeter settings
		for (i = 0; i < 2; i++) {
			if ((error = talonSRX->ConfigSetCustomParam(0, i, m_timeout)) != OKAY) {
				std::printf("2135: ERROR: %s Motor %s ConfigSetCustomParam error - %d\n", subsystem, name, error);
			}
		}

		// Initialize current limiting features
		if ((error = talonSRX->ConfigPeakCurrentLimit(0, m_timeout)) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s ConfigPeakCurrentLimit error - %d\n", subsystem, name, error);
		}
		if ((error = talonSRX->ConfigPeakCurrentDuration(0, m_timeout)) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s ConfigPeakCurrentDuration error - %d\n", subsystem, name, error);
		}
		if ((error = talonSRX->ConfigContinuousCurrentLimit(0, m_timeout)) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s ConfigContinuousCurrentLimit error - %d\n", subsystem, name, error);
		}

		std::printf("2135: %s Motor %s ID %d ver %d.%d is RESPONSIVE and INITIALIZED (error %d)\n",
				subsystem, name, deviceID, fwVersion/256, fwVersion&0xff, error);
	}
	else {
		std::printf("2135: ERROR: %s Motor %s ID %d ver %d.%d is UNRESPONSIVE, (error %d)\n",
				subsystem, name, deviceID, fwVersion/256, fwVersion&0xff, error);
	}

	return talonValid;
}

void TalonSRXUtils::TalonSRXFaultDump(const char *talonName, std::shared_ptr<WPI_TalonSRX> talonSRX) {
	int				fwVersion = 0;
	ErrorCode		error = OKAY;
	Faults			faults;
	StickyFaults	stickyFaults;

	std::printf("2135: %s --------------\n", talonName);

    // Check Talon SRX by getting device ID and validating firmware versions
	talonSRX->GetDeviceID();
	if ((error = talonSRX->GetLastError()) != OKAY) {
		std::printf("2135: ERROR: %s Motor %s GetDeviceID error - %d\n",
			talonSRX->GetSubsystem().c_str(), talonSRX->GetName().c_str(), error);
		return;
	}

	fwVersion = talonSRX->GetFirmwareVersion();
	if ((error = talonSRX->GetLastError()) != OKAY) {
		std::printf("2135: ERROR: %s Motor %s GetFirmwareVersion error - %d\n",
			talonSRX->GetSubsystem().c_str(), talonSRX->GetName().c_str(), error);
		return;
	}
	if (fwVersion != m_reqVersion) {
		std::printf("2135: WARNING: %s Motor %s Incorrect FW version %d.%d expected %d.%d\n",
			talonSRX->GetSubsystem().c_str(), talonSRX->GetName().c_str(), fwVersion/256, fwVersion%256, m_reqVersion/256, m_reqVersion%256);
		return;
	}

	// Now the Talon has been validated
	talonSRX->GetFaults(faults);
	talonSRX->GetStickyFaults(stickyFaults);
	talonSRX->ClearStickyFaults(100);

	if (faults.HasAnyFault()) {
		std::printf("At Least one fault below\n");
	if (faults.ForwardLimitSwitch)
		std::printf("\tForwardLimitSwitch\n");
	if (faults.ForwardSoftLimit)
		std::printf("\tForwardSoftLimit\n");
	if (faults.HardwareESDReset)
		std::printf("\tHardwareESDReset\n");
	if (faults.HardwareFailure)
		std::printf("\tHardwareFailure\n");
	if (faults.RemoteLossOfSignal)
		std::printf("\tRemoteLossOfSignal\n");
	if (faults.ResetDuringEn)
		std::printf("\tResetDuringEn\n");
	if (faults.ReverseLimitSwitch)
		std::printf("\tReverseLimitSwitch\n");
	if (faults.ReverseSoftLimit)
		std::printf("\tReverseSoftLimit\n");
	if  (faults.SensorOutOfPhase)
		std::printf("\tSensorOutOfPhase\n");
	if (faults.SensorOverflow)
		std::printf("\tSensorOverflow\n");
	if (faults.UnderVoltage)
		std::printf("\tUnderVoltage\n");
	}
	else {
		std::printf("2135: NO Talon SRX active faults detected\n");
	}

	if (stickyFaults.HasAnyFault()) {
		std::printf("At Least one STICKY fault below\n");
	if (stickyFaults.ForwardLimitSwitch)
		std::printf("\tForwardLimitSwitch\n");
	if (stickyFaults.ForwardSoftLimit)
		std::printf("\tForwardSoftLimit\n");
	if (stickyFaults.HardwareESDReset)
		std::printf("\tHardwareESDReset\n");
//	if (stickyFaults.HardwareFailure)
//		std::printf("\tHardwareFailure\n");
	if (stickyFaults.RemoteLossOfSignal)
		std::printf("\tRemoteLossOfSignal\n");
	if (stickyFaults.ResetDuringEn)
		std::printf("\tResetDuringEn\n");
	if (stickyFaults.ReverseLimitSwitch)
		std::printf("\tReverseLimitSwitch\n");
	if (stickyFaults.ReverseSoftLimit)
		std::printf("\tReverseSoftLimit\n");
	if  (stickyFaults.SensorOutOfPhase)
		std::printf("\tSensorOutOfPhase\n");
	if (stickyFaults.SensorOverflow)
		std::printf("\tSensorOverflow\n");
	if (stickyFaults.UnderVoltage)
		std::printf("\tUnderVoltage\n");
	}
	else {
		std::printf("2135: NO Talon SRX sticky faults detected\n");
	}
}

} /* namespace frc2135 */
