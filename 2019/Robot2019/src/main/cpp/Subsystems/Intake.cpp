
// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Subsystems/Intake.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

Intake::Intake() : frc::Subsystem("Intake") {
    std::printf("2135: IN Intake Constructor\n");
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    motorIN14.reset(new WPI_TalonSRX(14));
    
    
    panelDelivery.reset(new frc::DoubleSolenoid(0, 1, 6));
    AddChild("Panel Delivery", panelDelivery);
    

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    // Validate Talon SRX controllers, initialize and display firmware versions
    m_talonValidIN14 = frc2135::TalonSRXUtils::TalonSRXCheck(motorIN14, "IN", "M14"); 

     // Check if solenoids are functional or blacklisted
    if (panelDelivery->IsFwdSolenoidBlackListed())
        std::printf("2135: ERROR: IN Panel Delivery FWD Solenoid is BLACKLISTED\n");
    else
        std::printf("2135: IN Panel Delivery FWD Solenoid is FUNCTIONAL\n");
    if (panelDelivery->IsRevSolenoidBlackListed())
        std::printf("2135: ERROR: IN Panel Delivery REV Solenoid is BLACKLISTED\n");
    else
        std::printf("2135: IN Panel Delivery REV Solenoid is FUNCTIONAL\n");

    // Initialize Variables 
    // TODO: determine speeds (defaults are random)
    frc2135::RobotConfig* config = frc2135::RobotConfig::GetInstance();
    config->GetValueAsDouble("IN_AcquireSpeed", m_acquireSpeed, 0.50); 
    config->GetValueAsDouble("IN_HoldSpeed", m_holdSpeed, 0.25);
    config->GetValueAsDouble("IN_ExpelSpeed", m_expelSpeed, -0.75);

    // Set motor directions
    // Turn on Brake mode (not coast)
    // Set motor peak outputs
    if (m_talonValidIN14) { 
        motorIN14->SetInverted(false);
        motorIN14->SetNeutralMode(NeutralMode::Brake);
        motorIN14->ConfigVoltageCompSaturation(12.0, 0);
        motorIN14->EnableVoltageCompensation(true);

        motorIN14->ConfigPeakOutputForward(m_acquireSpeed, m_timeout);
        motorIN14->ConfigPeakOutputReverse(m_expelSpeed, m_timeout);
    }

    Initialize();
}

void Intake::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void Intake::Periodic() {
    double outputIN14 = 0.0, currentIN14 = 0.0;
    
    if (m_talonValidIN14) {
        outputIN14 = motorIN14->GetMotorOutputVoltage();
        currentIN14 = motorIN14->GetOutputCurrent();
    }

    if (m_gripperDebug) {
        frc::SmartDashboard::PutNumber("IN_Output_IN14", outputIN14);
        frc::SmartDashboard::PutNumber("IN_Current_IN14", currentIN14);
    }
}

///////////////////////////////////////////////////////////////////////////////

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS


// Put methods for controlling this subsystem
// here. Call these from Commands.
void Intake::Initialize(void) {
    std::printf("2135: IN Init\n");

    // Motor off
     if (m_talonValidIN14) 
        SetIntakeMotorDirection(INTAKE_STOP);

    // Solenoid retracted
     m_deliveryExtended = false;
     frc::SmartDashboard::PutBoolean("IN Delivery Extended", m_deliveryExtended);
     SetDeliverySolenoid(m_deliveryExtended);
 }

void Intake::SetIntakeMotorDirection(int direction) {
    const char *strName;
    double output = 0.0;        // Default: off

    switch(direction)
    {
    default:
    case INTAKE_STOP:
        strName = "STOP";
        break;
    case INTAKE_FORWARD:
        strName = "FORWARD";
        output = m_acquireSpeed; 
        break;
    case INTAKE_HOLD:
        strName = "HOLD";
        output = m_holdSpeed;
        break;
    case INTAKE_REVERSE:
        strName = "REVERSE";
        output = m_expelSpeed; 
        break;
    }

    std::printf("2135: Intake Set Speed - %s\n", strName); 

    if(m_talonValidIN14)
        motorIN14->Set(ControlMode::PercentOutput, output);
}

void Intake::SetDeliverySolenoid(bool extended) {
    m_deliveryExtended = extended;

    std::printf("2135: IN Hatch Panel Delivery - %s\n", (m_deliveryExtended) ? "EXTEND" : "RETRACT");
    frc::SmartDashboard::PutBoolean("IN Delivery Extended", m_deliveryExtended);

    panelDelivery->Set((m_deliveryExtended) ? panelDelivery->kForward : panelDelivery->kReverse);
}








