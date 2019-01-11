// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Subsystems/Prototype.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Commands/DriveTeleop.h"
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Prototype::Prototype() : frc::Subsystem("Prototype") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    talonSRX1.reset(new WPI_TalonSRX(21));
    talonSRX2.reset(new WPI_TalonSRX(22));

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    m_talonInvert1 = false;
    m_talonInvert2 = false;
}

void Prototype::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new DriveTeleop());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void Prototype::Periodic() {
    // Put code here to be run every loop

}

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS


// Put methods for controlling this subsystem
// here. Call these from Commands.

void Prototype::MoveWithJoystick(std::shared_ptr<frc::Joystick> jstick) {
    double speed1;
    double speed2;
    speed1 = jstick->GetY();
    speed2 = jstick->GetZ();
    talonSRX1->Set(ControlMode::PercentOutput, speed1);
    talonSRX2->Set(ControlMode::PercentOutput, speed2);
}

void Prototype::InvertMotor1() {
    talonSRX1->SetInverted(m_talonInvert1 == true ? false : true);
    m_talonInvert1 = (m_talonInvert1 == true ? false : true);
}

void Prototype::InvertMotor2() {
    talonSRX2->SetInverted((m_talonInvert2 == true ? false : true));
    m_talonInvert2 = (m_talonInvert1 == true ? false : true);
}
