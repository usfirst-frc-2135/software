// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include <OI.h>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "frc/smartdashboard/SmartDashboard.h"
#include "Commands/AutoDriveDist.h"
#include "Commands/AutoStop.h"
#include "Commands/DriveAlignPIDTurn.h"
#include "Commands/DriveAlignTurn.h"
#include "Commands/DriveReset.h"
#include "Commands/DriveShift.h"
#include "Commands/DriveTeleop.h"
#include "Commands/SpinColor.h"
#include "Commands/SpinRotation.h"


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

OI::OI() {
    // Process operator interface input here.
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
controlBoard.reset(new frc::Joystick(1));

sPRotation.reset(new frc::JoystickButton(controlBoard.get(), 2));
sPRotation->WhenPressed(new SpinRotation());
sPColor.reset(new frc::JoystickButton(controlBoard.get(), 1));
sPColor->WhenPressed(new SpinColor());
dStick.reset(new frc::Joystick(0));

shiftSpeed.reset(new frc::JoystickButton(dStick.get(), 1));
shiftSpeed->WhileHeld(new DriveShift(false));

    // SmartDashboard Buttons
    frc::SmartDashboard::PutData("Drive Align PID Turn: default", new DriveAlignPIDTurn(0.0));
    frc::SmartDashboard::PutData("Spin Rotation", new SpinRotation());
    frc::SmartDashboard::PutData("Spin Color", new SpinColor());
    frc::SmartDashboard::PutData("Drive Align Turn", new DriveAlignTurn());
    frc::SmartDashboard::PutData("Drive Reset", new DriveReset());
    frc::SmartDashboard::PutData("Auto Drive Dist: DEFAULT", new AutoDriveDist(0));

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS

    // Additional joystick if using separate joysticks
    frc2135::RobotConfig* config = frc2135::RobotConfig::GetInstance();
    config->GetValueAsBool("DT_SeparateJoysticks", m_separateJoysticks, false);
    if (m_separateJoysticks) {
        dStick2.reset(new frc::Joystick(2));
    }
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

std::shared_ptr<frc::Joystick> OI::getDStick() {
   return dStick;
}

std::shared_ptr<frc::Joystick> OI::getControlBoard() {
   return controlBoard;
}


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

// Returns null pointer or additional joystick if using separate joysticks
std::shared_ptr<frc::Joystick> OI::getDStick2() {
   return ( (m_separateJoysticks) ? dStick2 : nullptr);
}
