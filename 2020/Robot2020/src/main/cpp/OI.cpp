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
#include "Commands/AutoConvey.h"
#include "Commands/AutoDriveDist.h"
#include "Commands/AutoDriveTimed.h"
#include "Commands/AutoShoot.h"
#include "Commands/AutoShootDrive.h"
#include "Commands/AutoStop.h"
#include "Commands/ClimberDeploy.h"
#include "Commands/ClimberRun.h"
#include "Commands/ConveyorRun.h"
#include "Commands/DTBumpDownRampRate.h"
#include "Commands/DTBumpUpRampRate.h"
#include "Commands/DriveAlignPIDTurn.h"
#include "Commands/DriveAlignTurn.h"
#include "Commands/DriveModeToggle.h"
#include "Commands/DriveReset.h"
#include "Commands/DriveShift.h"
#include "Commands/DriveTeleop.h"
#include "Commands/IndexerDeploy.h"
#include "Commands/IntakeDeploy.h"
#include "Commands/IntakeRun.h"
#include "Commands/LedSet.h"
#include "Commands/ShooterRun.h"
#include "Commands/SpinColor.h"
#include "Commands/SpinRotation.h"


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

OI::OI() {
    // Process operator interface input here.
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
controlBoard2.reset(new frc::Joystick(2));

ledToggle.reset(new frc::JoystickButton(controlBoard2.get(), 1));
ledToggle->WhenPressed(new LedSet());
controlBoard.reset(new frc::Joystick(1));

spRotation.reset(new frc::JoystickButton(controlBoard.get(), 14));
spRotation->WhenPressed(new SpinRotation());
spColor.reset(new frc::JoystickButton(controlBoard.get(), 13));
spColor->WhenPressed(new SpinColor());
clDescend.reset(new frc::JoystickButton(controlBoard.get(), 12));
clDescend->WhenPressed(new ClimberRun(-1));
clAscend.reset(new frc::JoystickButton(controlBoard.get(), 11));
clAscend->WhenPressed(new ClimberRun(1));
clStow.reset(new frc::JoystickButton(controlBoard.get(), 10));
clStow->WhenPressed(new ClimberDeploy(false));
clDeploy.reset(new frc::JoystickButton(controlBoard.get(), 9));
clDeploy->WhenPressed(new ClimberDeploy(true));
shFire.reset(new frc::JoystickButton(controlBoard.get(), 8));
shFire->WhileHeld(new IndexerDeploy(false));
shRun.reset(new frc::JoystickButton(controlBoard.get(), 7));
shRun->WhileHeld(new ShooterRun(1));
cvUp.reset(new frc::JoystickButton(controlBoard.get(), 6));
cvUp->WhileHeld(new ConveyorRun(1));
cvDown.reset(new frc::JoystickButton(controlBoard.get(), 5));
cvDown->WhileHeld(new ConveyorRun(-1));
inAquire.reset(new frc::JoystickButton(controlBoard.get(), 4));
inAquire->WhileHeld(new IntakeRun(1));
inExpel.reset(new frc::JoystickButton(controlBoard.get(), 3));
inExpel->WhileHeld(new IntakeRun(-1));
inStow.reset(new frc::JoystickButton(controlBoard.get(), 2));
inStow->WhenPressed(new IntakeDeploy(false));
inDeploy.reset(new frc::JoystickButton(controlBoard.get(), 1));
inDeploy->WhenPressed(new IntakeDeploy(false));
dStick.reset(new frc::Joystick(0));

dtModeToggle.reset(new frc::JoystickButton(dStick.get(), 3));
dtModeToggle->WhenPressed(new DriveModeToggle());
dtAlignTurn.reset(new frc::JoystickButton(dStick.get(), 4));
dtAlignTurn->WhenPressed(new DriveAlignTurn());
dtPIDAlignTurn.reset(new frc::JoystickButton(dStick.get(), 2));
dtPIDAlignTurn->WhenPressed(new DriveAlignPIDTurn(0));
dtShiftSpeed.reset(new frc::JoystickButton(dStick.get(), 1));
dtShiftSpeed->WhileHeld(new DriveShift(false));

    // SmartDashboard Buttons
    frc::SmartDashboard::PutData("DT Bump Down Ramp Rate", new DTBumpDownRampRate());
    frc::SmartDashboard::PutData("DT Bump Up Ramp Rate", new DTBumpUpRampRate());
    frc::SmartDashboard::PutData("Led Set", new LedSet());
    frc::SmartDashboard::PutData("Spin Rotation", new SpinRotation());
    frc::SmartDashboard::PutData("Spin Color", new SpinColor());
    frc::SmartDashboard::PutData("Climber Run: CLIMBER_UP", new ClimberRun(1));
    frc::SmartDashboard::PutData("Climber Run: CLIMBER_DOWN", new ClimberRun(-1));
    frc::SmartDashboard::PutData("Climber Run: CLIMBER_STOP", new ClimberRun(0));
    frc::SmartDashboard::PutData("Climber Deploy: CLIMBER_STOW", new ClimberDeploy(false));
    frc::SmartDashboard::PutData("Climber Deploy: CLIMBER_DEPLOY", new ClimberDeploy(true));
    frc::SmartDashboard::PutData("Indexer Deploy: INDEXER_CLOSE", new IndexerDeploy(false));
    frc::SmartDashboard::PutData("Indexer Deploy: INDEXER_OPEN", new IndexerDeploy(true));
    frc::SmartDashboard::PutData("Shooter Run: SHOOTERSPEED_REVERSE", new ShooterRun(-1));
    frc::SmartDashboard::PutData("Shooter Run: SHOOTERSPEED_STOP", new ShooterRun(0));
    frc::SmartDashboard::PutData("Shooter Run: SHOOTERSPEED_FORWARD", new ShooterRun(1));
    frc::SmartDashboard::PutData("Conveyor Run: CONVEYORDIRECTION_STOP", new ConveyorRun(0));
    frc::SmartDashboard::PutData("Conveyor Run: CONVEYORDIRECTION_UP", new ConveyorRun(1));
    frc::SmartDashboard::PutData("Conveyor Run: CONVEYORDIRECTION_DOWN", new ConveyorRun(-1));
    frc::SmartDashboard::PutData("Intake Run: INTAKE_STOP", new IntakeRun(0));
    frc::SmartDashboard::PutData("Intake Run: INTAKE_ACQUIRE", new IntakeRun(1));
    frc::SmartDashboard::PutData("Intake Run: INTAKE_EXPEL", new IntakeRun(-1));
    frc::SmartDashboard::PutData("Intake Deploy: INTAKE_STOW", new IntakeDeploy(false));
    frc::SmartDashboard::PutData("Intake Deploy: INTAKE_DEPLOY", new IntakeDeploy(true));
    frc::SmartDashboard::PutData("Drive Mode Toggle", new DriveModeToggle());
    frc::SmartDashboard::PutData("Drive Align PID Turn: default", new DriveAlignPIDTurn(0.0));
    frc::SmartDashboard::PutData("Drive Align Turn", new DriveAlignTurn());
    frc::SmartDashboard::PutData("Drive Reset", new DriveReset());
    frc::SmartDashboard::PutData("Auto Shoot Drive", new AutoShootDrive());
    frc::SmartDashboard::PutData("Auto Drive Timed", new AutoDriveTimed(1));
    frc::SmartDashboard::PutData("Auto Drive Dist: DEFAULT", new AutoDriveDist(0));
    frc::SmartDashboard::PutData("Auto Convey: shoot", new AutoConvey(3));
    frc::SmartDashboard::PutData("Auto Shoot: shoot", new AutoShoot(3));
    frc::SmartDashboard::PutData("Auto Shoot: wait", new AutoShoot(6));

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

std::shared_ptr<frc::Joystick> OI::getControlBoard2() {
   return controlBoard2;
}


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

// Returns null pointer or additional joystick if using separate joysticks
std::shared_ptr<frc::Joystick> OI::getDStick2() {
   return ( (m_separateJoysticks) ? dStick2 : nullptr);
}
