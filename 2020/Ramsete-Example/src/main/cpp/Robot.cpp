/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>


void Robot::RobotInit() {
  frc::SmartDashboard::PutNumber("L_Ctr", 0.5);
  
  //  chooser.AddOption("B1", "Blue_Alliance_Team_1.wpilib.json");
  //  chooser.AddOption("B2", "Blue_Alliance_Team_2.wpilib.json"); 
  //  chooser.AddOption("B3", "Blue_Alliance_Team_3.wpilib.json");
  //  chooser.AddOption("R1", "Red_Alliance_Team_1.wpilib.json"); 
  //  chooser.AddOption("R2", "Red_Alliance_Team_2.wpilib.json"); 
  //  chooser.AddOption("R3", "Red_Alliance_Team_3.wpilib.json"); 
  //  chooser.AddOption("TS", "Test_Square.wpilib.json"); 
  //  chooser.AddOption("T1", "Test_Path_1.wpilib.json"); 
  //  chooser.AddOption("T3", "Test_Path_3.wpilib.json"); 
  //  chooser.AddOption("T4", "Test_Path_4.wpilib.json"); 

  // frc::SmartDashboard::PutData(&chooser);

}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want to run during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
  frc2::CommandScheduler::GetInstance().Run();
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

/**
 * This autonomous runs the autonomous command selected by your {@link
 * RobotContainer} class.
 */
void Robot::AutonomousInit() {
  m_autonomousCommand = m_container.GetAutonomousCommand();

  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Schedule();
  }
}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
  // This makes sure that the autonomous stops running when
  // teleop starts running. If you want the autonomous to
  // continue until interrupted by another command, remove
  // this line or comment it out.
  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Cancel();
    m_autonomousCommand = nullptr;
  }
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic() {}

/**
 * This function is called periodically during test mode.
 */
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
