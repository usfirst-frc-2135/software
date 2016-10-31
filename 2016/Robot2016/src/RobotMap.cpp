// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
std::shared_ptr<CANTalon> RobotMap::chassisMotorL2;
std::shared_ptr<Encoder> RobotMap::chassisLeftEncoder;
std::shared_ptr<PIDController> RobotMap::chassisLeftPID;
std::shared_ptr<CANTalon> RobotMap::chassisMotorR4;
std::shared_ptr<Encoder> RobotMap::chassisRightEncoder;
std::shared_ptr<PIDController> RobotMap::chassisRightPID;
std::shared_ptr<CANTalon> RobotMap::chassisMotorL3;
std::shared_ptr<CANTalon> RobotMap::chassisMotorR5;
std::shared_ptr<CANTalon> RobotMap::sweeperMotorAcquire1;
std::shared_ptr<CANTalon> RobotMap::sweeperMotorAcquire2;
std::shared_ptr<DoubleSolenoid> RobotMap::sweeperExtension;
std::shared_ptr<CANTalon> RobotMap::shooterLowerMotor;
std::shared_ptr<CANTalon> RobotMap::shooterUpperMotor;
std::shared_ptr<DoubleSolenoid> RobotMap::shooterFrameSolenoid;
std::shared_ptr<DoubleSolenoid> RobotMap::shooterFireSolenoid;
std::shared_ptr<DigitalOutput> RobotMap::lightPowerEnable;
std::shared_ptr<CANTalon> RobotMap::climberMotor;
std::shared_ptr<Compressor> RobotMap::pneumaticsCompressor;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION

void RobotMap::init() {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    LiveWindow *lw = LiveWindow::GetInstance();

    chassisMotorL2.reset(new CANTalon(2));
    lw->AddActuator("Chassis", "MotorL2", chassisMotorL2);
    
    chassisLeftEncoder.reset(new Encoder(0, 1, false, Encoder::k4X));
    lw->AddSensor("Chassis", "Left Encoder", chassisLeftEncoder);
    chassisLeftEncoder->SetDistancePerPulse(1.0);
    chassisLeftEncoder->SetPIDSourceType(PIDSourceType::kDisplacement);
    chassisLeftPID.reset(new PIDController(1.0, 0.0, 0.0,/* F: 0.0, */ chassisLeftEncoder.get(), chassisMotorL2.get(), 0.02));
    lw->AddActuator("Chassis", "LeftPID", chassisLeftPID);
    chassisLeftPID->SetContinuous(false); chassisLeftPID->SetAbsoluteTolerance(0.2); 
        chassisLeftPID->SetOutputRange(-1.0, 1.0);
    chassisMotorR4.reset(new CANTalon(4));
    lw->AddActuator("Chassis", "MotorR4", chassisMotorR4);
    
    chassisRightEncoder.reset(new Encoder(2, 3, false, Encoder::k4X));
    lw->AddSensor("Chassis", "Right Encoder", chassisRightEncoder);
    chassisRightEncoder->SetDistancePerPulse(1.0);
    chassisRightEncoder->SetPIDSourceType(PIDSourceType::kDisplacement);
    chassisRightPID.reset(new PIDController(1.0, 0.0, 0.0,/* F: 0.0, */ chassisRightEncoder.get(), chassisMotorR4.get(), 0.02));
    lw->AddActuator("Chassis", "RightPID", chassisRightPID);
    chassisRightPID->SetContinuous(false); chassisRightPID->SetAbsoluteTolerance(0.2); 
        chassisRightPID->SetOutputRange(-1.0, 1.0);
    chassisMotorL3.reset(new CANTalon(3));
    lw->AddActuator("Chassis", "MotorL3", chassisMotorL3);
    
    chassisMotorR5.reset(new CANTalon(5));
    lw->AddActuator("Chassis", "MotorR5", chassisMotorR5);
    
    sweeperMotorAcquire1.reset(new CANTalon(6));
    lw->AddActuator("Sweeper", "Motor Acquire 1", sweeperMotorAcquire1);
    
    sweeperMotorAcquire2.reset(new CANTalon(7));
    lw->AddActuator("Sweeper", "Motor Acquire 2", sweeperMotorAcquire2);
    
    sweeperExtension.reset(new DoubleSolenoid(0, 1, 6));
    lw->AddActuator("Sweeper", "Extension", sweeperExtension);
    
    shooterLowerMotor.reset(new CANTalon(8));
    lw->AddActuator("Shooter", "Lower Motor", shooterLowerMotor);
    
    shooterUpperMotor.reset(new CANTalon(9));
    lw->AddActuator("Shooter", "Upper Motor", shooterUpperMotor);
    
    shooterFrameSolenoid.reset(new DoubleSolenoid(0, 2, 5));
    lw->AddActuator("Shooter", "Frame Solenoid", shooterFrameSolenoid);
    
    shooterFireSolenoid.reset(new DoubleSolenoid(0, 3, 4));
    lw->AddActuator("Shooter", "Fire Solenoid", shooterFireSolenoid);
    
    lightPowerEnable.reset(new DigitalOutput(4));
    lw->AddActuator("Light", "Power Enable", lightPowerEnable);
    
    climberMotor.reset(new CANTalon(10));
    lw->AddActuator("Climber", "Motor", climberMotor);
    
    pneumaticsCompressor.reset(new Compressor(0));
    
    


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}
