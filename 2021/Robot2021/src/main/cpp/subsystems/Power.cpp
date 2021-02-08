// RobotBuilder Version: 3.1
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "subsystems/Power.h"
#include <frc/smartdashboard/SmartDashboard.h>

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

Power::Power()
{
    SetName("Power");

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    SetSubsystem("Power");

 AddChild("Pdp", &m_pdp);


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    m_pdp.ResetTotalEnergy();

    Initialize ();
}

void Power::Periodic()
{
    static int  periodicInterval = 0;

    // Put code here to be run every loop

    // Only update indicators every 100 ms to cut down on network traffic
    if (periodicInterval++ % 5 == 0)
    {
        if (m_powerDebug  > 0)
        {
            char    chanStr[32];
            int     chan;

            frc::SmartDashboard::PutNumber("PDP Temp", m_pdp.GetTemperature());
            frc::SmartDashboard::PutNumber("PDP Total Amps", m_pdp.GetTotalCurrent());
            frc::SmartDashboard::PutNumber("PDP Total Watts", m_pdp.GetTotalPower());
            frc::SmartDashboard::PutNumber("PDP Total Joules", m_pdp.GetTotalEnergy());

            // Show all currents if more debugging is needed
            if (periodicInterval % 50 == 0)
            {
                for (chan = 0; chan <= 15; chan++)
                {
                    std::sprintf(chanStr, "PDP Chan %2d A\n", chan);
                    frc::SmartDashboard::PutNumber(chanStr, m_pdp.GetCurrent(chan));
                }
            }
        }
    }
}

void Power::SimulationPeriodic()
{
    // This method will be called once per scheduler run when in simulation

}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS


// Put methods for controlling this subsystem
// here. Call these from Commands.

void Power::Initialize(void)
{
    std::printf("2135: PDP Init\n");
    std::printf("2135: PDP Voltage %5.1f Volts\n", m_pdp.GetVoltage());
}

void Power::FaultDump(void)
{
    // Print out PDP faults and clear sticky ones
    std::printf("2135: %s --------------\n", "PDP FAULTS");
    std::printf("2135: Temperature      %5.1f\n", m_pdp.GetTemperature());
    std::printf("2135: Input Voltage    %5.1f\n", m_pdp.GetVoltage());
    for (int i = 0; i <= 15; i++)
        std::printf("2135: Chan %2d Current %5.1f\n", i, m_pdp.GetCurrent(i));
    std::printf("2135: Total Current    %5.1f\n", m_pdp.GetTotalCurrent());
    std::printf("2135: Total Power      %5.1f\n", m_pdp.GetTotalPower());
    std::printf("2135: Total Energy     %5.1f\n", m_pdp.GetTotalEnergy());
    m_pdp.ResetTotalEnergy();
    m_pdp.ClearStickyFaults();
}
