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
SpeedController* RobotMap::chassisLeftDriveMotor = NULL;
Encoder* RobotMap::chassisLeftDriveEncoder = NULL;
PIDController* RobotMap::chassisLeftDrivePID = NULL;
SpeedController* RobotMap::chassisRightDriveMotor = NULL;
Encoder* RobotMap::chassisRightDriveEncoder = NULL;
PIDController* RobotMap::chassisRightDrivePID = NULL;
DoubleSolenoid* RobotMap::transmissionShifterSolenoid = NULL;
DoubleSolenoid* RobotMap::sweeperArmExtendSolenoid = NULL;
SpeedController* RobotMap::sweeperMotorWheels = NULL;
SpeedController* RobotMap::shooterRetractMotor = NULL;
DigitalInput* RobotMap::shooterRetractLimit1 = NULL;
DigitalInput* RobotMap::shooterRetractLimit2 = NULL;
Encoder* RobotMap::shooterRetractEncoder = NULL;
DoubleSolenoid* RobotMap::triggerShooterTriggerSolenoid = NULL;
DoubleSolenoid* RobotMap::ballGateCloseSolenoid = NULL;
DigitalInput* RobotMap::ballGateBallDetectLimit = NULL;
Compressor* RobotMap::pneumaticsCompressor = NULL;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
DriverStation* RobotMap::driverStation = NULL;
RobotDrive* RobotMap::driveTrain = NULL;
void RobotMap::init() {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	LiveWindow* lw = LiveWindow::GetInstance();
	chassisLeftDriveMotor = new Talon(1, 1);
	lw->AddActuator("Chassis", "Left Drive Motor", (Talon*) chassisLeftDriveMotor);
	
	chassisLeftDriveEncoder = new Encoder(1, 1, 1, 2, true, Encoder::k4X);
	lw->AddSensor("Chassis", "Left Drive  Encoder", chassisLeftDriveEncoder);
	chassisLeftDriveEncoder->SetDistancePerPulse(0.03490658503988659);
        chassisLeftDriveEncoder->SetPIDSourceParameter(Encoder::kDistance);
        chassisLeftDriveEncoder->Start();
	chassisLeftDrivePID = new PIDController(7.2, 0.0, 0.0,/* F: 0.0, */ chassisLeftDriveEncoder, chassisLeftDriveMotor, 0.02);
	lw->AddActuator("Chassis", "Left Drive PID", chassisLeftDrivePID);
	chassisLeftDrivePID->SetContinuous(false); chassisLeftDrivePID->SetAbsoluteTolerance(0.5); 
        chassisLeftDrivePID->SetOutputRange(-0.7, 0.7);
	chassisRightDriveMotor = new Talon(1, 2);
	lw->AddActuator("Chassis", "Right Drive Motor", (Talon*) chassisRightDriveMotor);
	
	chassisRightDriveEncoder = new Encoder(1, 3, 1, 4, true, Encoder::k4X);
	lw->AddSensor("Chassis", "Right Drive Encoder", chassisRightDriveEncoder);
	chassisRightDriveEncoder->SetDistancePerPulse(0.03490658503988659);
        chassisRightDriveEncoder->SetPIDSourceParameter(Encoder::kDistance);
        chassisRightDriveEncoder->Start();
	chassisRightDrivePID = new PIDController(7.2, 0.0, 0.0,/* F: 0.0, */ chassisRightDriveEncoder, chassisRightDriveMotor, 0.02);
	lw->AddActuator("Chassis", "Right Drive PID", chassisRightDrivePID);
	chassisRightDrivePID->SetContinuous(false); chassisRightDrivePID->SetAbsoluteTolerance(0.5); 
        chassisRightDrivePID->SetOutputRange(-0.7, 0.7);
	transmissionShifterSolenoid = new DoubleSolenoid(1, 1, 2);      
	
	
	sweeperArmExtendSolenoid = new DoubleSolenoid(1, 3, 4);      
	
	
	sweeperMotorWheels = new Talon(1, 3);
	lw->AddActuator("Sweeper Motor", "Wheels", (Talon*) sweeperMotorWheels);
	
	shooterRetractMotor = new Talon(1, 4);
	lw->AddActuator("Shooter", "Retract Motor", (Talon*) shooterRetractMotor);
	
	shooterRetractLimit1 = new DigitalInput(1, 7);
	lw->AddSensor("Shooter", "Retract Limit 1", shooterRetractLimit1);
	
	shooterRetractLimit2 = new DigitalInput(1, 8);
	lw->AddSensor("Shooter", "Retract Limit 2", shooterRetractLimit2);
	
	shooterRetractEncoder = new Encoder(1, 5, 1, 6, false, Encoder::k4X);
	lw->AddSensor("Shooter", "Retract Encoder", shooterRetractEncoder);
	shooterRetractEncoder->SetDistancePerPulse(1.0);
        shooterRetractEncoder->SetPIDSourceParameter(Encoder::kRate);
        shooterRetractEncoder->Start();
	triggerShooterTriggerSolenoid = new DoubleSolenoid(1, 7, 8);      
	
	
	ballGateCloseSolenoid = new DoubleSolenoid(1, 5, 6);      
	
	
	ballGateBallDetectLimit = new DigitalInput(1, 9);
	lw->AddSensor("Ball Gate", "Ball Detect Limit", ballGateBallDetectLimit);
	
	pneumaticsCompressor = new Compressor(1, 14, 1, 1);
	
	
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	printf( "2135: RobotMap Init\n" );
	driverStation = DriverStation::GetInstance();
	driveTrain = new RobotDrive(chassisLeftDriveMotor, chassisRightDriveMotor);
//	driveTrain->SetExpiration(0.5);
}
