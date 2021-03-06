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

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
std::shared_ptr<WPI_TalonSRX> RobotMap::drivetrainMotorL1;
std::shared_ptr<WPI_TalonSRX> RobotMap::drivetrainMotorR3;
std::shared_ptr<frc::DifferentialDrive> RobotMap::drivetrainDiffDrive;
std::shared_ptr<WPI_TalonSRX> RobotMap::drivetrainMotorL2;
std::shared_ptr<WPI_TalonSRX> RobotMap::drivetrainMotorR4;
std::shared_ptr<frc::DoubleSolenoid> RobotMap::drivetrainShifter;
std::shared_ptr<WPI_TalonSRX> RobotMap::elevatorMotorL7;
std::shared_ptr<WPI_TalonSRX> RobotMap::elevatorMotorR8;
std::shared_ptr<frc::DigitalInput> RobotMap::elevatorHallLimit;
std::shared_ptr<WPI_TalonSRX> RobotMap::gripperMotorL11;
std::shared_ptr<WPI_TalonSRX> RobotMap::gripperMotorR12;
std::shared_ptr<WPI_TalonSRX> RobotMap::wristMotorW14;
std::shared_ptr<frc::Compressor> RobotMap::pneumaticsCompressor;
std::shared_ptr<frc::PowerDistributionPanel> RobotMap::powerPDP;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION

void RobotMap::init() {
	// Remove all LiveWindow calls to add objects that are deprecated (redundant)
	// TODO: See if this is fixed in 2019 beta when RobotBuilder is updated

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    frc::LiveWindow *lw = frc::LiveWindow::GetInstance();

    drivetrainMotorL1.reset(new WPI_TalonSRX(1));
    
    
    drivetrainMotorR3.reset(new WPI_TalonSRX(3));
    
    
    drivetrainDiffDrive.reset(new frc::DifferentialDrive(*drivetrainMotorL1, *drivetrainMotorR3));
//    lw->AddActuator("Drivetrain", "Diff Drive", drivetrainDiffDrive);
    drivetrainDiffDrive->SetSafetyEnabled(true);
        drivetrainDiffDrive->SetExpiration(0.25);
        drivetrainDiffDrive->SetMaxOutput(1.0);

    drivetrainMotorL2.reset(new WPI_TalonSRX(2));
    
    
    drivetrainMotorR4.reset(new WPI_TalonSRX(4));
    
    
    drivetrainShifter.reset(new frc::DoubleSolenoid(0, 0, 7));
//    lw->AddActuator("Drivetrain", "Shifter", drivetrainShifter);
    
    elevatorMotorL7.reset(new WPI_TalonSRX(7));
    
    
    elevatorMotorR8.reset(new WPI_TalonSRX(8));
    
    
    elevatorHallLimit.reset(new frc::DigitalInput(0));
//    lw->AddSensor("Elevator", "Hall Limit", elevatorHallLimit);
    
    gripperMotorL11.reset(new WPI_TalonSRX(11));
    
    
    gripperMotorR12.reset(new WPI_TalonSRX(12));
    
    
    wristMotorW14.reset(new WPI_TalonSRX(14));
    
    
    pneumaticsCompressor.reset(new frc::Compressor(0));
//    lw->AddActuator("Pneumatics", "Compressor", pneumaticsCompressor);
    
    powerPDP.reset(new frc::PowerDistributionPanel(0));
//    lw->AddSensor("Power", "PDP", powerPDP);
    


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS

    // The PowerDistributionPanel object has a bug which will cause CAN timeouts if
    // it is referenced from a separate thread--like our main thread. This call will
    // disable the default telemetry in the object so our does not time out.
    // See the thread on ChiefDelphi and the PDP Users Manual from CTRE for more info
    // It would be better if it just disabled only PDP telemetry, but this does not work.
    // TODO: Check to see if this is fixed in 2019 beta

    lw->DisableAllTelemetry();
    //lw->DisableTelemetry(powerPDP);
}
