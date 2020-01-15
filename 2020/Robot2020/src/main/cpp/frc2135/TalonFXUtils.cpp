/*
 * TalonFXUtils.cpp
 *
 *  Created on: Jan 14, 2020
 *      Author: PHS_User
 */

#include <frc2135/TalonFXUtils.h>
#include <chrono>

namespace frc2135 {

TalonFXUtils::TalonFXUtils() {
	// Auto-generated constructor stub
}

TalonFXUtils::~TalonFXUtils() {
	// Auto-generated destructor stub
}

bool TalonFXUtils::TalonFXCheck(std::shared_ptr<WPI_TalonFX> talonFX, const char *subsystem, const char *name) {
	int			i;
	int			deviceID = 0;
	int			fwVersion = 0;
	bool		talonValid = false;
	ErrorCode	error = OKAY;

	// Configure subsystem and component name
    talonFX->SetName(subsystem, name);
   	std::printf("2135: TalonFX Subsystem %s Name %s\n", talonFX->GetSubsystem().c_str(), talonFX->GetName().c_str());

    // Display Talon FX firmware versions
	deviceID = talonFX->GetDeviceID();
	if ((error = talonFX->GetLastError()) != OKAY) {
		std::printf("2135: ERROR: %s Motor %s GetDeviceID error - %d\n", 
			subsystem, name, error);
		return error;
	}

	for (i = 0; i < m_retries; i++) {
		fwVersion = talonFX->GetFirmwareVersion();
		if ((error = talonFX->GetLastError()) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s ID %d GetFirmwareVersion error - %d\n", 
				subsystem, name, deviceID, error);
			return error;
		}
		if (fwVersion == m_reqVersion) {
			talonValid = true;
			break;
		}
		else {
			std::printf("2135: WARNING: %s Motor %s ID %d Incorrect FW version %d.%d expected %d.%d\n",
				subsystem, name, deviceID, fwVersion/256, fwVersion%256, m_reqVersion/256, m_reqVersion%256);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}

	if (talonValid) {
			// Initialize Talon FX to all factory defaults
		if ((error = talonFX->ConfigFactoryDefault(m_timeout)) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s ID %d ConfigFactoryDefault error - %d\n", 
				subsystem, name, deviceID, error);
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

void TalonFXUtils::TalonFXFaultDump(const char *talonName, std::shared_ptr<WPI_TalonFX> talonFX) {
	int				fwVersion = 0;
	ErrorCode		error = OKAY;
	Faults			faults;
	StickyFaults	stickyFaults;

	// Print out Talon FX faults and clear sticky ones
	std::printf("2135: %s -------------- %s\n", "Talon FX", talonName);

    // Check Talon FX by getting device ID and validating firmware versions
	talonFX->GetDeviceID();
	if ((error = talonFX->GetLastError()) != OKAY) {
		std::printf("2135: ERROR: %s Motor %s GetDeviceID error - %d\n",
			talonFX->GetSubsystem().c_str(), talonFX->GetName().c_str(), error);
		return;
	}

	fwVersion = talonFX->GetFirmwareVersion();
	if ((error = talonFX->GetLastError()) != OKAY) {
		std::printf("2135: ERROR: %s Motor %s GetFirmwareVersion error - %d\n",
			talonFX->GetSubsystem().c_str(), talonFX->GetName().c_str(), error);
		return;
	}
	if (fwVersion != m_reqVersion) {
		std::printf("2135: WARNING: %s Motor %s Incorrect FW version %d.%d expected %d.%d\n",
			talonFX->GetSubsystem().c_str(), talonFX->GetName().c_str(), fwVersion/256, fwVersion%256, m_reqVersion/256, m_reqVersion%256);
		return;
	}

	// Now the Talon has been validated
	talonFX->GetFaults(faults);
	talonFX->GetStickyFaults(stickyFaults);
	talonFX->ClearStickyFaults(100);

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
		std::printf("2135: NO Talon FX active faults detected\n");
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
		std::printf("2135: NO Talon FX sticky faults detected\n");
	}
}

} /* namespace frc2135 */
