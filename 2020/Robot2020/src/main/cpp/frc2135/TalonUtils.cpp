/*
 * TalonUtils.cpp
 *
 *  Created on: Jan 14, 2020
 *      Author: PHS_User
 */

#include <frc2135/TalonUtils.h>
#include <chrono>

namespace frc2135 {

TalonUtils::TalonUtils() {
	// Auto-generated constructor stub
}

TalonUtils::~TalonUtils() {
	// Auto-generated destructor stub
}

bool TalonUtils::TalonCheck(std::shared_ptr<WPI_BaseMotorController> talon, const char *subsystem, const char *name) {
	int			i;
	int			deviceID = 0;
	int			fwVersion = 0;
	bool		talonValid = false;
	ErrorCode	error = OKAY;

	// Configure subsystem and component name
// Ignore the warning that it is deprecated
// TODO: WE WILL REMOVE ALL DEPRECATED CODE IN OFF-SEASON
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    talon->SetName(subsystem, name);
   	std::printf("2135: Talon Subsystem %s Name %s\n", talon->GetSubsystem().c_str(), talon->GetName().c_str());
#pragma GCC diagnostic pop

    // Display Talon firmware versions
	deviceID = talon->GetDeviceID();
	if ((error = talon->GetLastError()) != OKAY) {
		std::printf("2135: ERROR: %s Motor %s GetDeviceID error - %d\n",
			subsystem, name, error);
		return error;
	}

	for (i = 0; i < m_retries; i++) {
		fwVersion = talon->GetFirmwareVersion();
		if ((error = talon->GetLastError()) != OKAY) {
			std::printf("2135: ERROR: %s Motor %s ID %d GetFirmwareVersion error - %d\n",
				subsystem, name, deviceID, error);
			return error;
		}
		if (fwVersion >= m_reqVersion) {
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
			// Initialize Talon to all factory defaults
		if ((error = talon->ConfigFactoryDefault(m_timeout)) != OKAY) {
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

void TalonUtils::TalonFaultDump(const char *talonName, std::shared_ptr<WPI_BaseMotorController> talon) {
	int				fwVersion = 0;
	ErrorCode		error = OKAY;
	Faults			faults;
	StickyFaults	stickyFaults;

	// Print out Talon faults and clear sticky ones
	std::printf("2135: %s -------------- %s\n", "Talon ", talonName);

    // Check Talon by getting device ID and validating firmware versions
	talon->GetDeviceID();
	if ((error = talon->GetLastError()) != OKAY) {
// Ignore the warning that it is deprecated
// TODO: WE WILL REMOVE ALL DEPRECATED CODE IN OFF-SEASON
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
		std::printf("2135: ERROR: %s Motor %s GetDeviceID error - %d\n",
			talon->GetSubsystem().c_str(), talon->GetName().c_str(), error);
#pragma GCC diagnostic pop
		return;
	}

	fwVersion = talon->GetFirmwareVersion();
	if ((error = talon->GetLastError()) != OKAY) {
// Ignore the warning that it is deprecated
// TODO: WE WILL REMOVE ALL DEPRECATED CODE IN OFF-SEASON
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
		std::printf("2135: ERROR: %s Motor %s GetFirmwareVersion error - %d\n",
			talon->GetSubsystem().c_str(), talon->GetName().c_str(), error);
#pragma GCC diagnostic pop
		return;
	}
	if (fwVersion != m_reqVersion) {
// Ignore the warning that it is deprecated
// TODO: WE WILL REMOVE ALL DEPRECATED CODE IN OFF-SEASON
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
		std::printf("2135: WARNING: %s Motor %s Incorrect FW version %d.%d expected %d.%d\n",
			talon->GetSubsystem().c_str(), talon->GetName().c_str(), fwVersion/256, fwVersion%256, m_reqVersion/256, m_reqVersion%256);
#pragma GCC diagnostic pop
		return;
	}

	// Now the Talon has been validated
	talon->GetFaults(faults);
	talon->GetStickyFaults(stickyFaults);
	talon->ClearStickyFaults(100);

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
