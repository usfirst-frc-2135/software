/*
 * TalonUtils.cpp
 *
 *  Created on: Jan 14, 2020
 *      Author: PHS_User
 */

#include <frc/RobotBase.h>
#include <frc2135/TalonUtils.h>
#include <chrono>

namespace frc2135
{

TalonUtils::TalonUtils()
{
    // Auto-generated constructor stub
}

TalonUtils::~TalonUtils()
{
    // Auto-generated destructor stub
}

bool TalonUtils::TalonCheck(WPI_BaseMotorController &talon, const char *subsystem, const char *name)
{
    int         i;
    int         deviceID = 0;
    int         fwVersion = 0;
    bool        talonValid = false;
    ErrorCode   error = OKAY;

    // Configure subsystem

    // Display Talon firmware versions
    deviceID = talon.GetDeviceID();
    if ((error = talon.GetLastError()) != OKAY)
    {
        std::printf("2135: ERROR: %s Motor %s GetDeviceID error - %d\n", subsystem, name, error);
        return error;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(250));

    for (i = 0; i < m_retries; i++)
    {
        fwVersion = talon.GetFirmwareVersion();
        if ((error = talon.GetLastError()) != OKAY)
        {
            std::printf("2135: ERROR: %s Motor %s ID %d GetFirmwareVersion error - %d\n", subsystem, name, deviceID, error);
            return error;
        }
        if (fwVersion >= m_reqVersion)
        {
            talonValid = true;
            break;
        }
        else
            std::printf("2135: WARNING: %s Motor %s ID %d Incorrect FW version %u.%u expected %u.%u\n",
                subsystem, name, deviceID, fwVersion / 256, fwVersion  & 0xff, m_reqVersion / 256, m_reqVersion & 0xff);

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    if (talonValid)
    {
            // Initialize Talon to all factory defaults
        if ((error = talon.ConfigFactoryDefault(kCANTimeout)) != OKAY)
            std::printf("2135: ERROR: %s Motor %s ID %d ConfigFactoryDefault error - %d\n",
                subsystem, name, deviceID, error);

        std::printf("2135: %s Motor %s ID %d ver %u.%u is RESPONSIVE and INITIALIZED (error %d)\n",
                subsystem, name, deviceID, fwVersion / 256, fwVersion & 0xff, error);
    }
    else
        std::printf("2135: ERROR: %s Motor %s ID %d ver %u.%u is UNRESPONSIVE, (error %d)\n",
                subsystem, name, deviceID, fwVersion / 256, fwVersion & 0xff, error);

    if (!frc::RobotBase::IsReal())
        talonValid = true;

    return talonValid;
}

void TalonUtils::TalonFaultDump(const char *talonName, WPI_BaseMotorController &talon)
{
    int             fwVersion = 0;
    ErrorCode       error = OKAY;
    Faults          faults;
    StickyFaults    stickyFaults;

    // Print out Talon faults and clear sticky ones
    std::printf("2135: %s -------------- %s\n", "Talon ", talonName);

    // Check Talon by getting device ID and validating firmware versions
    talon.GetDeviceID();
    if ((error = talon.GetLastError()) != OKAY)
    {
        std::printf("2135: ERROR: Motor %s GetDeviceID error - %d\n", talonName, error);
        return;
    }

    fwVersion = talon.GetFirmwareVersion();
    if ((error = talon.GetLastError()) != OKAY)
    {
        std::printf("2135: ERROR: Motor %s GetFirmwareVersion error - %d\n", talonName, error);
        return;
    }
    if (fwVersion != m_reqVersion)
    {
        std::printf("2135: WARNING: Motor %s Incorrect FW version %u.%u expected %u.%u\n", talonName,
            fwVersion / 256, fwVersion & 0xff, m_reqVersion / 256, m_reqVersion & 0xff);
        return;
    }

    // Now the Talon has been validated
    talon.GetFaults(faults);
    talon.GetStickyFaults(stickyFaults);
    talon.ClearStickyFaults(100);

    if (faults.HasAnyFault())
    {
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
    else
        std::printf("2135: NO Talon FX active faults detected\n");

    if (stickyFaults.HasAnyFault())
    {
        std::printf("At Least one STICKY fault below\n");
        if (stickyFaults.ForwardLimitSwitch)
            std::printf("\tForwardLimitSwitch\n");
        if (stickyFaults.ForwardSoftLimit)
            std::printf("\tForwardSoftLimit\n");
        if (stickyFaults.HardwareESDReset)
            std::printf("\tHardwareESDReset\n");
    //    if (stickyFaults.HardwareFailure)
    //        std::printf("\tHardwareFailure\n");
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
    else
        std::printf("2135: NO Talon FX sticky faults detected\n");
}

///////////////////////////////////////////////////////////////////////////////
//
//    Pigeon IMU
//
bool TalonUtils::PigeonIMUInitialize(PigeonIMU &pigeonPtr)
{
    int i;
    int retries = 5;
    int deviceID = 0;
    int pigeonVersion = 0;
    bool pigeonValid = false;
    ErrorCode error = OKAY;
    char subsystem[] = "DT";
    char name[] = "Pigeon IMU";

    std::printf("2135: TalonFX Subsystem %s Name %s\n", subsystem, name);

    // Display Pigeon IMU firmware versions
    deviceID = pigeonPtr.GetDeviceNumber();
    if ((error = pigeonPtr.GetLastError()) != OKAY)
    {
        std::printf("2135: ERROR: %s %s GetDeviceNumber error - %d\n", subsystem, name, error);
        return error;
    }

    for (i = 0; i < retries; i++)
    {
        pigeonVersion = pigeonPtr.GetFirmwareVersion();
        if ((error = pigeonPtr.GetLastError()) != OKAY)
        {
            std::printf("2135: ERROR: %s %s ID %d GetFirmwareVersion error - %d\n", subsystem, name, deviceID, error);
            return error;
        }
        else if (pigeonVersion == m_reqPigeonVer)
        {
            pigeonValid = true;
            break;
        }
        else
        {
            std::printf("2135: WARNING: %s %s ID %d Incorrect FW version %u.%u expected %u.%u\n",
                subsystem, name, deviceID, pigeonVersion / 256, pigeonVersion & 0xff, m_reqPigeonVer / 256, m_reqPigeonVer & 0xff);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    if (pigeonValid)
    {
        // Initialize Pigeon IMU to all factory defaults
        if ((error = pigeonPtr.ConfigFactoryDefault(kCANTimeout)) != OKAY)
        {
            std::printf("2135: ERROR: %s %s ID %d ConfigFactoryDefault error - %d\n", subsystem, name, deviceID, error);
            pigeonValid = false;
        }

        double headingDeg = pigeonPtr.GetFusedHeading();
        bool angleIsGood = (pigeonPtr.GetState() == PigeonIMU::Ready) ? true : false;
        std::printf("2135: %s %s ID %d fused m_headingDeg %5.1f angle is %s degrees\n",
            subsystem, name, deviceID, headingDeg, (angleIsGood) ? "TRUE" : "FALSE");

        pigeonPtr.SetYaw(0.0, kCANTimeout);
        if ((error = pigeonPtr.GetLastError()) != OKAY)
        {
            std::printf("2135: ERROR: %s %s ID %d SetFusedHeading error - %d\n", subsystem, name, deviceID, error);
            pigeonValid = false;
        }

        pigeonPtr.SetFusedHeading(0.0, kCANTimeout);
        if ((error = pigeonPtr.GetLastError()) != OKAY)
        {
            std::printf("2135: ERROR: %s %s ID %d SetYaw error - %d\n", subsystem, name, deviceID, error);
            pigeonValid = false;
        }

        std::printf("2135: %s %s ID %d ver %u.%u is RESPONSIVE and INITIALIZED (error %d)\n",
            subsystem, name, deviceID, pigeonVersion / 256, pigeonVersion & 0xff, error);
    }
    else
    {
        std::printf("2135: ERROR: %s %s ID %d ver %u.%u is UNRESPONSIVE, (error %d)\n",
            subsystem, name, deviceID, pigeonVersion / 256, pigeonVersion & 0xff, error);
        pigeonValid = false;
    }

    return pigeonValid;
}

void TalonUtils::PigeonIMUFaultDump(const char *pigeonName, PigeonIMU &pigeonPtr)
{
    int             fwVersion = 0;
    ErrorCode       error = OKAY;
    PigeonIMU_Faults          faults;
    PigeonIMU_StickyFaults    stickyFaults;

    // Print out PigeonIMU faults and clear sticky ones
    std::printf("2135: %s -------------- %s\n", "PigeonIMU ", pigeonName);

    // Check PigeonIMU by getting device ID and validating firmware versions
    pigeonPtr.GetDeviceNumber();
    if ((error = pigeonPtr.GetLastError()) != OKAY)
    {
        std::printf("2135: ERROR: PigeonIMU Gyro GetDeviceID error - %d\n", error);
        return;
    }

    fwVersion = pigeonPtr.GetFirmwareVersion();
    if ((error = pigeonPtr.GetLastError()) != OKAY)
    {
        std::printf("2135: ERROR: PigeonIMU Gyro GetFirmwareVersion error - %d\n", error);
        return;
    }
    if (fwVersion != m_reqVersion)
    {
        std::printf("2135: WARNING: PigeonIMU Gyro Incorrect FW version %u.%u expected %u.%u\n",
             fwVersion / 256, fwVersion & 0xff, m_reqVersion / 256, m_reqVersion & 0xff);
        return;
    }

    // Now the PigeonIMU has been validated
    pigeonPtr.GetFaults(faults);
    pigeonPtr.GetStickyFaults(stickyFaults);
    pigeonPtr.ClearStickyFaults(100);

    if (faults.HasAnyFault())
        std::printf("2135: ERROR: %s %s ID %d has a FAULT - %d\n", "DT", "PigeonIMU", 2, faults.ToBitfield());
    else
        std::printf("2135: NO PigeonIMU sticky faults detected\n");
}

} /* namespace frc2135 */
