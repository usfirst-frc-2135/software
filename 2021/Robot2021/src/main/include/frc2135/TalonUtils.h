/*
 * TalonUtils.h
 *
 *  Created on: Jan 14, 2020
 *      Author: PHS_User
 */

#pragma once

#include <ctre/Phoenix.h>

namespace frc2135
{
    class TalonUtils
    {
    private:
        static const int kCANTimeout = 30; // CAN timeout in msec to wait for response
        static const int m_retries = 4;    // Number of version check attempts

        static const int m_reqVersion = ((20 * 256) + 1);   // Talon version is 20.1
        static const int m_reqPigeonVer = ((20 * 256) + 0); // Pigeon IMU version is 20.0

    public:
        TalonUtils();
        virtual ~TalonUtils();
        static bool TalonCheck(WPI_BaseMotorController &talon, const char *subsystem, const char *name);
        static void TalonFaultDump(const char *talonName, WPI_BaseMotorController &talonPtr);
        static bool PigeonIMUInitialize(PigeonIMU &pigeonPtr);
        static void PigeonIMUFaultDump(const char *pigeonName, PigeonIMU &pigeonPtr);
    };

} /* namespace frc2135 */
