/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/TimedRobot.h>
#include <frc/XboxController.h>

#include "Drivetrain.h"

class Robot : public frc::TimedRobot {
 public:
  void AutonomousPeriodic() override {
    TeleopPeriodic();
    m_drive.UpdateOdometry();
  }

  // void TeleopInit() override {
  //   create timer
  //   std::printf("Timer created");
  //   frc::Timer *timer = new frc::Timer();
  //   timer->Start();
  // }
  void TeleopPeriodic() override {
    // Get the x speed. We are inverting this because Xbox controllers return
    // negative values when we push forward.
    double controllerY = m_controller.GetY(frc::GenericHID::kLeftHand);
    //dead zone for controller
    if (controllerY < 0.06 && controllerY > -0.06) {
      controllerY = 0;
    }
    const auto xSpeed =
        controllerY * Drivetrain::kMaxSpeed;

    // Get the rate of angular rotation. We are inverting this because we want a
    // positive value when we pull to the left (remember, CCW is positive in
    // mathematics). Xbox controllers return positive values when you pull to
    // the right by default.
    //const auto rot = -m_controller.GetX(frc::GenericHID::kRightHand) *
                     //Drivetrain::kMaxAngularSpeed;
    const auto rot = units::radians_per_second_t(0);

    //std::printf("time %i\n", timer->Get());
    std::printf("controller: %f\n", controllerY);
    std::printf("xSpeed: %f\n", xSpeed);
    m_drive.Drive(xSpeed, rot);
    
  }

 private:
  frc::XboxController m_controller{0};
  Drivetrain m_drive;

};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
