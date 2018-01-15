// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "ctre/Phoenix.h"

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
std::shared_ptr<WPI_TalonSRX> RobotMap::chassisMotorL1;
std::shared_ptr<WPI_TalonSRX> RobotMap::chassisMotorR3;
std::shared_ptr<frc::DifferentialDrive> RobotMap::chassisDiffDrive;
std::shared_ptr<WPI_TalonSRX> RobotMap::chassisMotorL2;
std::shared_ptr<WPI_TalonSRX> RobotMap::chassisMotorR4;
std::shared_ptr<frc::DoubleSolenoid> RobotMap::chassisShifter;
std::shared_ptr<WPI_TalonSRX> RobotMap::gripperMotor5;
std::shared_ptr<WPI_TalonSRX> RobotMap::gripperMotor6;
std::shared_ptr<WPI_TalonSRX> RobotMap::elevatorMotor7;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION

void RobotMap::init() {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    frc::LiveWindow *lw = frc::LiveWindow::GetInstance();

    chassisMotorL1.reset(new WPI_TalonSRX(1));
    
    
    chassisMotorR3.reset(new WPI_TalonSRX(3));
    
    
    chassisDiffDrive.reset(new frc::DifferentialDrive(*chassisMotorL1, *chassisMotorR3));
    
    chassisDiffDrive->SetSafetyEnabled(true);
        chassisDiffDrive->SetExpiration(0.1);
        chassisDiffDrive->SetMaxOutput(1.0);

    chassisMotorL2.reset(new WPI_TalonSRX(2));
    
    
    chassisMotorR4.reset(new WPI_TalonSRX(4));
    
    
    chassisShifter.reset(new frc::DoubleSolenoid(0, 0, 7));
    lw->AddActuator("Chassis", "Shifter", chassisShifter);
    
    gripperMotor5.reset(new WPI_TalonSRX(5));
    
    
    gripperMotor6.reset(new WPI_TalonSRX(6));
    
    
    elevatorMotor7.reset(new WPI_TalonSRX(7));
    
    


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}
