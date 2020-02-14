/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/TimedRobot.h>
#include <frc/Joystick.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "Drivetrain.h"

class Robot : public frc::TimedRobot {
 public:
  std::shared_ptr<frc::Joystick> dStick{new frc::Joystick (0)};
  void AutonomousPeriodic() override {
    TeleopPeriodic();
    m_drive.UpdateOdometry();
  }

  double MoveWithJoysticks (std::shared_ptr<frc::Joystick> throttleJstick) {
    double xValue = 0.0;
    double yValue = 0.0;
    xValue = throttleJstick->GetX();
    yValue = throttleJstick->GetZ();
    //dead zone for controller
     if (yValue < 0.06 && yValue > -0.06) {
       yValue = 0;
     }
     return yValue;
  }

  void TeleopPeriodic() override {
    // Get the x speed. We are inverting this because Xbox controllers return
    // negative values when we push forward.
    const auto xSpeed =
        MoveWithJoysticks(dStick) * Drivetrain::kMaxSpeed;
    frc::SmartDashboard::PutNumber("Joystick", MoveWithJoysticks(dStick));

    // Get the rate of angular rotation. We are inverting this because we want a
    // positive value when we pull to the left (remember, CCW is positive in
    // mathematics). Xbox controllers return positive values when you pull to
    // the right by default.
    const auto rot = -dStick->GetX() * Drivetrain::kMaxAngularSpeed;
    // const auto rot = units::radians_per_second_t(0);

    //std::printf("time %i\n", timer->Get());
    //std::printf("yValue: %f\n", yValue);
    //std::printf("xSpeed: %f\n", xSpeed);
    frc::SmartDashboard::PutNumber("xSpeed (in m/s)", double(xSpeed));
    frc::SmartDashboard::PutNumber("rot (in radians/s)", double(rot));
    m_drive.Drive(xSpeed, rot);
    
  }

 private:
  Drivetrain m_drive;

};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
