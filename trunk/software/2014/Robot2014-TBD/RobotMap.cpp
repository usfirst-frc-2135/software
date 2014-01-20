// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
Encoder* RobotMap::chassisLeftEncoder = NULL;
Encoder* RobotMap::chassisRightEncoder = NULL;
SpeedController* RobotMap::chassisLeftMotor = NULL;
SpeedController* RobotMap::chassisRightMotor = NULL;
RobotDrive* RobotMap::chassisRobotDrive = NULL;
Compressor* RobotMap::pneumaticsCompressor = NULL;
DoubleSolenoid* RobotMap::transmissionShifter = NULL;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
PIDController* RobotMap::driveControlLeft = NULL;
PIDController* RobotMap::driveControlRight = NULL;
void RobotMap::init() {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	LiveWindow* lw = LiveWindow::GetInstance();
	chassisLeftEncoder = new Encoder(1, 1, 1, 2, true, Encoder::k4X);
	lw->AddSensor("Chassis", "LeftEncoder", chassisLeftEncoder);
	chassisLeftEncoder->SetDistancePerPulse(1.0);
        chassisLeftEncoder->SetPIDSourceParameter(Encoder::kDistance);
        chassisLeftEncoder->Start();
	chassisRightEncoder = new Encoder(1, 3, 1, 4, false, Encoder::k4X);
	lw->AddSensor("Chassis", "Right Encoder", chassisRightEncoder);
	chassisRightEncoder->SetDistancePerPulse(1.0);
        chassisRightEncoder->SetPIDSourceParameter(Encoder::kDistance);
        chassisRightEncoder->Start();
	chassisLeftMotor = new Talon(1, 1);
	lw->AddActuator("Chassis", "Left Motor", (Talon*) chassisLeftMotor);
	
	chassisRightMotor = new Talon(1, 2);
	lw->AddActuator("Chassis", "Right Motor", (Talon*) chassisRightMotor);
	
	chassisRobotDrive = new RobotDrive(chassisLeftMotor, chassisRightMotor);
	
	chassisRobotDrive->SetSafetyEnabled(true);
        chassisRobotDrive->SetExpiration(0.5);
        chassisRobotDrive->SetSensitivity(0.5);
        chassisRobotDrive->SetMaxOutput(1.0);
        chassisRobotDrive->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
        chassisRobotDrive->SetInvertedMotor(RobotDrive::kRearRightMotor, true);        
	pneumaticsCompressor = new Compressor(1, 14, 1, 1);
	
	
	transmissionShifter = new DoubleSolenoid(1, 1, 2);      
	
	
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	driveControlLeft = new PIDController(0.2, 0.0, 0.0, 0.0, chassisLeftEncoder, chassisLeftMotor);
	driveControlRight = new PIDController(0.2, 0.0, 0.0, 0.0, chassisRightEncoder, chassisRightMotor);
	SmartDashboard::PutNumber("Output Range", 1.0);
}
