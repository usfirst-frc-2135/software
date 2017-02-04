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
std::shared_ptr<CANTalon> RobotMap::chassisMotorL1;
std::shared_ptr<CANTalon> RobotMap::chassisMotorR3;
std::shared_ptr<RobotDrive> RobotMap::chassisRobotDrive;
std::shared_ptr<CANTalon> RobotMap::chassisMotorL2;
std::shared_ptr<CANTalon> RobotMap::chassisMotorR4;
std::shared_ptr<AnalogGyro> RobotMap::chassisGyro;
std::shared_ptr<DoubleSolenoid> RobotMap::chassisShifter;
std::shared_ptr<CANTalon> RobotMap::intakeMotor;
std::shared_ptr<DoubleSolenoid> RobotMap::intakeArmDeploy;
std::shared_ptr<CANTalon> RobotMap::agitatorMotor;
std::shared_ptr<CANTalon> RobotMap::shooterMotor;
std::shared_ptr<Servo> RobotMap::shooterBallGate;
std::shared_ptr<DoubleSolenoid> RobotMap::deliveryGearRelease;
std::shared_ptr<DoubleSolenoid> RobotMap::deliveryDoorOpen;
std::shared_ptr<CANTalon> RobotMap::climberMotor;
std::shared_ptr<Compressor> RobotMap::pneumaticsCompressor;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION

void RobotMap::init() {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    LiveWindow *lw = LiveWindow::GetInstance();

    chassisMotorL1.reset(new CANTalon(1));
    lw->AddActuator("Chassis", "MotorL1", chassisMotorL1);
    
    chassisMotorR3.reset(new CANTalon(3));
    lw->AddActuator("Chassis", "MotorR3", chassisMotorR3);
    
    chassisRobotDrive.reset(new RobotDrive(chassisMotorL1, chassisMotorR3));
    
    chassisRobotDrive->SetSafetyEnabled(true);
        chassisRobotDrive->SetExpiration(0.1);
        chassisRobotDrive->SetSensitivity(0.5);
        chassisRobotDrive->SetMaxOutput(1.0);
        chassisRobotDrive->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
    chassisMotorL2.reset(new CANTalon(2));
    lw->AddActuator("Chassis", "MotorL2", chassisMotorL2);
    
    chassisMotorR4.reset(new CANTalon(4));
    lw->AddActuator("Chassis", "MotorR4", chassisMotorR4);
    
    chassisGyro.reset(new AnalogGyro(0));
    lw->AddSensor("Chassis", "Gyro", chassisGyro);
    chassisGyro->SetSensitivity(0.007);
    chassisShifter.reset(new DoubleSolenoid(0, 0, 7));
    lw->AddActuator("Chassis", "Shifter", chassisShifter);
    
    intakeMotor.reset(new CANTalon(8));
    lw->AddActuator("Intake", "Motor", intakeMotor);
    
    intakeArmDeploy.reset(new DoubleSolenoid(0, 1, 6));
    lw->AddActuator("Intake", "Arm Deploy", intakeArmDeploy);
    
    agitatorMotor.reset(new CANTalon(12));
    lw->AddActuator("Agitator", "Motor", agitatorMotor);
    
    shooterMotor.reset(new CANTalon(16));
    lw->AddActuator("Shooter", "Motor", shooterMotor);
    
    shooterBallGate.reset(new Servo(0));
    lw->AddActuator("Shooter", "Ball Gate", shooterBallGate);
    
    deliveryGearRelease.reset(new DoubleSolenoid(0, 2, 5));
    lw->AddActuator("Delivery", "Gear Release", deliveryGearRelease);
    
    deliveryDoorOpen.reset(new DoubleSolenoid(0, 3, 4));
    lw->AddActuator("Delivery", "Door Open", deliveryDoorOpen);
    
    climberMotor.reset(new CANTalon(20));
    lw->AddActuator("Climber", "Motor", climberMotor);
    
    pneumaticsCompressor.reset(new Compressor(0));
    
    


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}
