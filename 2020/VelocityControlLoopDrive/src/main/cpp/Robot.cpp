/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/TimedRobot.h>
#include <frc/Joystick.h>

#include "Drivetrain.h"

class Robot : public frc::TimedRobot {
 public:
  std::shared_ptr<frc::Joystick> dStick{0};
  std::shared_ptr<frc::Joystick> dStick2{0};
  void AutonomousPeriodic() override {
    std::printf("first print");
    TeleopPeriodic();
    m_drive.UpdateOdometry();
  }

  // void TeleopInit() override {
  //   create timer
  //   std::printf("Timer created");
  //   frc::Timer *timer = new frc::Timer();
  //   timer->Start();
  // }

  double MoveWithJoysticks (std::shared_ptr<frc::Joystick> throttleJstick, std::shared_ptr<frc::Joystick> turnJstick) {
    double xValue = 0.0;
    double yValue = 0.0;
    std::printf("third print");
    if (turnJstick == nullptr) {
      xValue = throttleJstick->GetX();
      yValue = throttleJstick->GetZ();
    }
    else {
      xValue = turnJstick->GetX();
      yValue = throttleJstick->GetY();
    }
    std::printf("fourth print");
    //dead zone for controller
     if (yValue < 0.06 && yValue > -0.06) {
       yValue = 0;
     }
     return yValue;
  }

  void TeleopPeriodic() override {
    // Get the x speed. We are inverting this because Xbox controllers return
    // negative values when we push forward.
    // double controllerY = m_controller.GetY(frc::GenericHID::kLeftHand);
    std::printf("second print");
    const auto xSpeed =
        MoveWithJoysticks(dStick, dStick2) * Drivetrain::kMaxSpeed;

    // Get the rate of angular rotation. We are inverting this because we want a
    // positive value when we pull to the left (remember, CCW is positive in
    // mathematics). Xbox controllers return positive values when you pull to
    // the right by default.
    //const auto rot = -m_controller.GetX(frc::GenericHID::kRightHand) *
                     //Drivetrain::kMaxAngularSpeed;
    const auto rot = units::radians_per_second_t(0);

    //std::printf("time %i\n", timer->Get());
    //std::printf("yValue: %f\n", yValue);
    std::printf("xSpeed: %f\n", xSpeed);
    m_drive.Drive(xSpeed, rot);
    
  }

 private:
  Drivetrain m_drive;

};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
