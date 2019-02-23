// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Subsystems/Pneumatics.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Pneumatics::Pneumatics() : frc::Subsystem("Pneumatics") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    pcm.reset(new frc::Compressor(0));
    AddChild("PCM", pcm);

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
}

void Pneumatics::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void Pneumatics::Periodic() {
    // Put code here to be run every loop
    double  outputComp = 0.0;

    outputComp = pcm->GetCompressorCurrent();
    frc::SmartDashboard::PutNumber("PCM_Output_Comp", outputComp);
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Pneumatics::Initialize(void) {
    
}

void Pneumatics::FaultDump(void) {
	
	// Print out PCM faults and clear sticky ones
	std::printf("2135: %s --------------\n", "PCM FAULTS");
	int		i;
	if (pcm->GetCompressorCurrentTooHighStickyFault())
		std::printf("\tCurrentTooHighFault\n");
	if (pcm->GetCompressorNotConnectedFault())
		std::printf("\tCompressorNotConnectedFault\n");
	if (pcm->GetCompressorShortedFault())
		std::printf("\tCompressorShortedFault\n");
	pcm->ClearAllPCMStickyFaults();
}

