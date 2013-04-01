// RobotBuilder Version: 0.0.2
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
SpeedController* RobotMap::chassisLeft = NULL;
SpeedController* RobotMap::chassisRight = NULL;
RobotDrive* RobotMap::chassisDriveTrain = NULL;
Encoder* RobotMap::chassisLeftEncoder = NULL;
Encoder* RobotMap::chassisRightEncoder = NULL;
Gyro* RobotMap::chassisGyro = NULL;
DoubleSolenoid* RobotMap::transmissionShifter = NULL;
SpeedController* RobotMap::conveyorMotor = NULL;
SpeedController* RobotMap::azimuthMotor = NULL;
SpeedController* RobotMap::shooterWheels = NULL;
Compressor* RobotMap::pneumaticsAirCompressor = NULL;
Servo* RobotMap::cameraServo = NULL;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
DriverStation* RobotMap::driverStation = NULL;
DriverStationLCD* RobotMap::driverStationLCD = NULL;
ADXL345_I2C* RobotMap::accelerometer = NULL;
void RobotMap::init() {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	LiveWindow* lw = LiveWindow::GetInstance();
	chassisLeft = new Victor(1, 1);
	lw->AddActuator("Chassis", "Left", (Victor*) chassisLeft);
	
	chassisRight = new Victor(1, 2);
	lw->AddActuator("Chassis", "Right", (Victor*) chassisRight);
	
	chassisDriveTrain = new RobotDrive(chassisLeft, chassisRight);
	
	chassisDriveTrain->SetSafetyEnabled(true);
        chassisDriveTrain->SetExpiration(0.25);
        chassisDriveTrain->SetSensitivity(0.5);
        chassisDriveTrain->SetMaxOutput(1.0);
        chassisDriveTrain->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
        chassisDriveTrain->SetInvertedMotor(RobotDrive::kRearRightMotor, true);        
	chassisLeftEncoder = new Encoder(1, 1, 1, 2, false, Encoder::k4X);
	lw->AddSensor("Chassis", "Left Encoder", chassisLeftEncoder);
	chassisLeftEncoder->SetDistancePerPulse(0.03490658503988659);
        chassisLeftEncoder->SetPIDSourceParameter(Encoder::kDistance);
        chassisLeftEncoder->Start();
	chassisRightEncoder = new Encoder(1, 3, 1, 4, true, Encoder::k4X);
	lw->AddSensor("Chassis", "Right Encoder", chassisRightEncoder);
	chassisRightEncoder->SetDistancePerPulse(0.03490658503988659);
        chassisRightEncoder->SetPIDSourceParameter(Encoder::kDistance);
        chassisRightEncoder->Start();
	chassisGyro = new Gyro(1, 1);
	lw->AddSensor("Chassis", "Gyro", chassisGyro);
	chassisGyro->SetSensitivity(0.007);
	transmissionShifter = new DoubleSolenoid(1, 1, 2);      
	
	
	conveyorMotor = new Victor(1, 3);
	lw->AddActuator("Conveyor", "Motor", (Victor*) conveyorMotor);
	
	azimuthMotor = new Victor(1, 4);
	lw->AddActuator("Azimuth", "Motor", (Victor*) azimuthMotor);
	
	shooterWheels = new Victor(1, 5);
	lw->AddActuator("Shooter", "Wheels", (Victor*) shooterWheels);
	
	pneumaticsAirCompressor = new Compressor(1, 14, 1, 1);
	
	
	cameraServo = new Servo(1, 10);
	lw->AddActuator("Camera", "Servo", cameraServo);
	
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	driverStation = DriverStation::GetInstance();
	driverStationLCD = DriverStationLCD::GetInstance();
	accelerometer = new ADXL345_I2C( 1, ADXL345_I2C::kRange_2G );
}
