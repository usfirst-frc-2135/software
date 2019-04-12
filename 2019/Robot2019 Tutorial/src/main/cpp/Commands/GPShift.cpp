// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Commands/GPShift.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

GPShift::GPShift(): frc::Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES

    // Initialize all subsystems HATCH PANEL to CARGO
    Initialize();
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void GPShift::Initialize() {

    m_cargoActive = !m_cargoActive;

    Robot::oi->SetCargo(m_cargoActive);
    printf("2135: Game Piece - %s\n", (m_cargoActive) ? "CARGO" : "HATCH PANEL");
    // Show RED for cargo active and GREEN for hatch active
    frc::SmartDashboard::PutBoolean("CMP_GPShift", !m_cargoActive);

    // If the last setting was true (cargo), then it will flip to false (hatch panel)
}

// Called repeatedly when this Command is scheduled to run
void GPShift::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool GPShift::IsFinished() {
    return true;
}

// Called once after isFinished returns true
void GPShift::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void GPShift::Interrupted() {
}
