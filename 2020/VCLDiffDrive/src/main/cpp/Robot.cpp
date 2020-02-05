/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <frc/drive/DifferentialDrive.h>
#include "Drivetrain.h"

class Robot : public frc::TimedRobot {
  //frc  ::WPI_TalonSRX m_leftMotor{1}
  //frc::WPI_TalonSRX m_rightMotor{3}
  //frc::DifferentialDrive m_robotDrive{m_leftMotor, m_rightMotor};
  frc::Joystick m_controller{0};

 public:
  // //void AutonomousPeriodic() override {
     void TeleopPeriodic();
     m_drive.UpdateOdometry();
   };

  void TeleopPeriodic() override {
        // Get the x speed. We are inverting this because Xbox controllers return
        // negative values when we push forward.
         const auto xSpeed = 
            -m_controller.GetY(frc::GenericHID::kLeftHand) * Drivetrain::kMaxSpeed;

       // Get the rate of angular rotation. We are inverting this because we want a
      // positive value when we pull to the left (remember, CCW is positive in
     // mathematics). Xbox controllers return positive values when you pull to
    // the right by default.
        const auto rot = -m_controller.GetX(frc::GenericHID::kRightHand) * Drivetrain::kMaxAngularSpeed;

    m_drive.Drive(xSpeed, rot);

  }

 private:
  frc::Joystick m_controller{0}
  Drivetrain m_drive;

};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
