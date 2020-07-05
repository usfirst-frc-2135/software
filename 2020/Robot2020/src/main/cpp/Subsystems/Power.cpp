// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include <Subsystems/Power.h>
#include <frc/smartdashboard/SmartDashboard.h>
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Power::Power() : frc::Subsystem("Power")
{
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
pdp.reset(new frc::PowerDistributionPanel(0));
AddChild("Pdp", pdp);


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    pdp->ResetTotalEnergy();

    std::printf("2135: PDP Voltage %5.1f Volts\n", pdp->GetVoltage());
}

void Power::InitDefaultCommand()
{
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void Power::Periodic()
{
    static int  periodicInterval = 0;

    // Put code here to be run every 20 msec loop

    // Only update indicators every 100 ms to cut down on network traffic
	if (periodicInterval++ % 5 == 0)
	{
		if (m_powerDebug  > 0)
		{
			char	chanStr[32];
			int		chan;

			frc::SmartDashboard::PutNumber("PDP Temp", pdp->GetTemperature());
			frc::SmartDashboard::PutNumber("PDP Total Amps", pdp->GetTotalCurrent());
			frc::SmartDashboard::PutNumber("PDP Total Watts", pdp->GetTotalPower());
			frc::SmartDashboard::PutNumber("PDP Total Joules", pdp->GetTotalEnergy());

        	// Show all currents if more debugging is needed
			if (periodicInterval % 50 == 0)
			{
				for (chan = 0; chan <= 15; chan++)
				{
					std::sprintf(chanStr, "PDP Chan %2d A\n", chan);
					frc::SmartDashboard::PutNumber(chanStr, pdp->GetCurrent(chan));
				}
			}
		}
	}
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS


// Put methods for controlling this subsystem
// here. Call these from Commands.

void Power::Initialize(void)
{

}

void Power::FaultDump(void)
{
	// Print out PDP faults and clear sticky ones
	std::printf("2135: %s --------------\n", "PDP FAULTS");
	std::printf("2135: Temperature      %5.1f\n", pdp->GetTemperature());
	std::printf("2135: Input Voltage    %5.1f\n", pdp->GetVoltage());
	for (int i = 0; i <= 15; i++)
		std::printf("2135: Chan %2d Current %5.1f\n", i, pdp->GetCurrent(i));
	std::printf("2135: Total Current    %5.1f\n", pdp->GetTotalCurrent());
	std::printf("2135: Total Power      %5.1f\n", pdp->GetTotalPower());
	std::printf("2135: Total Energy     %5.1f\n", pdp->GetTotalEnergy());
	pdp->ResetTotalEnergy();
	pdp->ClearStickyFaults();
}
