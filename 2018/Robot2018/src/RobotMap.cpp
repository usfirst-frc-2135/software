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
#include "RobotDefaults.h"
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "ctre/Phoenix.h"

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#ifdef ROBOTNOTSTANDALONE
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
std::shared_ptr<WPI_TalonSRX> RobotMap::drivetrainMotorL1;
std::shared_ptr<WPI_TalonSRX> RobotMap::drivetrainMotorR3;
std::shared_ptr<frc::DifferentialDrive> RobotMap::drivetrainDiffDrive;
std::shared_ptr<WPI_TalonSRX> RobotMap::drivetrainMotorL2;
std::shared_ptr<WPI_TalonSRX> RobotMap::drivetrainMotorR4;
std::shared_ptr<frc::DoubleSolenoid> RobotMap::drivetrainShifter;
std::shared_ptr<WPI_TalonSRX> RobotMap::gripperMotorL7;
std::shared_ptr<WPI_TalonSRX> RobotMap::gripperMotorR8;
std::shared_ptr<WPI_TalonSRX> RobotMap::elevatorMotorL11;
std::shared_ptr<WPI_TalonSRX> RobotMap::elevatorMotorR12;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
#endif

void RobotMap::init() {
#ifdef ROBOTNOTSTANDALONE
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    frc::LiveWindow *lw = frc::LiveWindow::GetInstance();

    drivetrainMotorL1.reset(new WPI_TalonSRX(1));
    
    
    drivetrainMotorR3.reset(new WPI_TalonSRX(3));
    
    
    drivetrainDiffDrive.reset(new frc::DifferentialDrive(*drivetrainMotorL1, *drivetrainMotorR3));
    lw->AddActuator("Drivetrain", "Diff Drive", drivetrainDiffDrive);
    drivetrainDiffDrive->SetSafetyEnabled(true);
        drivetrainDiffDrive->SetExpiration(0.1);
        drivetrainDiffDrive->SetMaxOutput(1.0);

    drivetrainMotorL2.reset(new WPI_TalonSRX(2));
    
    
    drivetrainMotorR4.reset(new WPI_TalonSRX(4));
    
    
    drivetrainShifter.reset(new frc::DoubleSolenoid(0, 0, 7));
    lw->AddActuator("Drivetrain", "Shifter", drivetrainShifter);
    
    gripperMotorL7.reset(new WPI_TalonSRX(7));
    
    
    gripperMotorR8.reset(new WPI_TalonSRX(8));
    
    
    elevatorMotorL11.reset(new WPI_TalonSRX(11));
    
    
    elevatorMotorR12.reset(new WPI_TalonSRX(0));
    
    


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
#endif
}
