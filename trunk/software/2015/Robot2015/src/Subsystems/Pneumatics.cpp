// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.




#include "Pneumatics.h"
#include "../RobotMap.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "../Commands/CompressorOn.h"
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

Pneumatics::Pneumatics() : Subsystem("Pneumatics") {
	printf("2135: Pneumatics init\n");
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	compressor = RobotMap::pneumaticsCompressor;
	analogInput1 = RobotMap::pneumaticsAnalogInput1;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
}
    
void Pneumatics::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
	SetDefaultCommand(new CompressorOn());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
//
// Enable the compressor
//
void Pneumatics::StartCompressor( void )
{
	compressor->Start();
}
//
// Disable the compressor
//
void Pneumatics::StopCompressor( void )
{
	compressor->Stop();
}

double Pneumatics::CheckTemperature( void )
{
	double m_voltage = analogInput1->GetAverageVoltage();
	m_temp = 100 * (m_voltage) - 50;
	return m_temp;
}
