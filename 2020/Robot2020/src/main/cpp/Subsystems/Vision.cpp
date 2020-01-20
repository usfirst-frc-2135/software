// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include <Subsystems/Vision.h>
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Vision::Vision() : frc::Subsystem("Vision") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    table = nt::NetworkTableInstance::GetDefault().GetTable("limelight"); 
    table->PutNumber("ledMode", 0); 
}

void Vision::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void Vision::Periodic() {
    // Put code here to be run every loop
    targetOffsetAngle_Horizontal = table->GetNumber("tx", 0.0);
    targetOffsetAngle_Vertical = table->GetNumber("ty", 0.0); 
    targetArea = table->GetNumber("ta", 0.0); 
    targetSkew = table->GetNumber ("ts", 0.0); 

    frc::SmartDashboard::PutNumber("VI_HORZ_OFFSET_ANGLE", targetOffsetAngle_Horizontal);
    frc::SmartDashboard::PutNumber("VI_VERT_OFFSET_ANGLE", targetOffsetAngle_Vertical);
    frc::SmartDashboard::PutNumber("VI_TARGET_AREA", targetArea);
    frc::SmartDashboard::PutNumber("VI_TARGET_SKEW", targetSkew);
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS


// Put methods for controlling this subsystem
// here. Call these from Commands.

