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
std::shared_ptr<TalonSRX> RobotMap::chassisMotorL1;
std::shared_ptr<TalonSRX> RobotMap::chassisMotorR3;
//std::shared_ptr<RobotDrive> RobotMap::chassisRobotDrive;
std::shared_ptr<TalonSRX> RobotMap::chassisMotorL2;
std::shared_ptr<TalonSRX> RobotMap::chassisMotorR4;
std::shared_ptr<DoubleSolenoid> RobotMap::chassisShifter;
std::shared_ptr<TalonSRX> RobotMap::intakeMotor8;
std::shared_ptr<TalonSRX> RobotMap::intakeMotor9;
std::shared_ptr<TalonSRX> RobotMap::agitatorMotor12;
std::shared_ptr<TalonSRX> RobotMap::shooterMotor14;
std::shared_ptr<Servo> RobotMap::shooterBallGate;
std::shared_ptr<DigitalOutput> RobotMap::shooterPowerEnable;
std::shared_ptr<DoubleSolenoid> RobotMap::deliveryGearDoor;
std::shared_ptr<TalonSRX> RobotMap::climberMotor18;
std::shared_ptr<TalonSRX> RobotMap::climberMotor19;
std::shared_ptr<Compressor> RobotMap::pneumaticsCompressor;
//std::shared_ptr<PowerDistributionPanel> RobotMap::powerPDP;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
std::shared_ptr<frc::DifferentialDrive> RobotMap::chassisDrive;

	std::shared_ptr<ADXRS450_Gyro> RobotMap::chassisGyro;

void RobotMap::init() {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
//    LiveWindow *lw = LiveWindow::GetInstance();

    chassisMotorL1.reset(new TalonSRX(1));
//	TODO: CTRE Libraries: LiveWindow not implemented on TalonSRX
//    lw->AddActuator("Chassis", "MotorL1", chassisMotorL1);
    
    chassisMotorR3.reset(new TalonSRX(3));
//    lw->AddActuator("Chassis", "MotorR3", chassisMotorR3);

//	TODO: RobotDrive not working - disabled
//    chassisRobotDrive.reset(new RobotDrive(chassisMotorL1, chassisMotorR3));
//
//    chassisRobotDrive->SetSafetyEnabled(true);
//        chassisRobotDrive->SetExpiration(0.1);
//        chassisRobotDrive->SetSensitivity(0.5);
//        chassisRobotDrive->SetMaxOutput(1.0);
//
//        chassisRobotDrive->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
    chassisMotorL2.reset(new TalonSRX(2));
//    lw->AddActuator("Chassis", "MotorL2", chassisMotorL2);
    
    chassisMotorR4.reset(new TalonSRX(4));
//    lw->AddActuator("Chassis", "MotorR4", chassisMotorR4);
    
    chassisShifter.reset(new DoubleSolenoid(0, 0, 7));
//    lw->AddActuator("Chassis", "Shifter", chassisShifter);
    
    intakeMotor8.reset(new TalonSRX(8));
//    lw->AddActuator("Intake", "Motor8", intakeMotor8);
    
    intakeMotor9.reset(new TalonSRX(9));
//    lw->AddActuator("Intake", "Motor9", intakeMotor9);
    
    agitatorMotor12.reset(new TalonSRX(12));
//    lw->AddActuator("Agitator", "Motor12", agitatorMotor12);
    
    shooterMotor14.reset(new TalonSRX(14));
//    lw->AddActuator("Shooter", "Motor14", shooterMotor14);
    
    shooterBallGate.reset(new Servo(0));
//    lw->AddActuator("Shooter", "Ball Gate", shooterBallGate);
    
    shooterPowerEnable.reset(new DigitalOutput(0));
//    lw->AddActuator("Shooter", "Power Enable", shooterPowerEnable);
    
    deliveryGearDoor.reset(new DoubleSolenoid(0, 1, 6));
//    lw->AddActuator("Delivery", "Gear Door", deliveryGearDoor);
    
    climberMotor18.reset(new TalonSRX(18));
//    lw->AddActuator("Climber", "Motor18", climberMotor18);
    
    climberMotor19.reset(new TalonSRX(19));
//    lw->AddActuator("Climber", "Motor19", climberMotor19);
    
    pneumaticsCompressor.reset(new Compressor(0));
    
    
//    powerPDP.reset(new PowerDistributionPanel(0));
//    lw->AddSensor("Power", "PDP", powerPDP);


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
//    chassisDrive.reset(new frc::DifferentialDrive(*chassisLeftGroup, *chassisRightGroup));
    chassisDrive.reset(new frc::DifferentialDrive(chassisMotorL1->GetWPILIB_SpeedController(), chassisMotorR3->GetWPILIB_SpeedController()));

    chassisDrive->SetSafetyEnabled(true);
        chassisDrive->SetExpiration(0.1);
        chassisDrive->SetMaxOutput(1.0);

    chassisGyro.reset(new ADXRS450_Gyro(frc::SPI::Port::kOnboardCS0));
//    lw->AddSensor("Chassis", "Gyro", chassisGyro);
    chassisGyro->Calibrate();
}
