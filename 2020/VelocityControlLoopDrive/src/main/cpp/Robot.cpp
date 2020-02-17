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

class Robot : public frc::TimedRobot
{
public:
  std::shared_ptr<frc::Joystick> dStick{ new frc::Joystick (0) };
  void AutonomousPeriodic() override
  {
    TeleopPeriodic();
    m_drive.UpdateOdometry();
  }

  void TeleopInit() override
  {

  }

  void TeleopPeriodic() override
  {
    // Get the y speed.
    double yValue = dStick->GetZ();
    //dead zone for controller
    if (yValue < 0.06 && yValue > -0.06)
      yValue = 0;
    frc::SmartDashboard::PutNumber("Joystick Y", yValue);

    const auto ySpeed = yValue * Drivetrain::kMaxSpeed;

    // Get the rate of angular rotation.
    double xValue = dStick->GetX();
    //dead zone for controller
    if (xValue < 0.06 && xValue > -0.06)
      xValue = 0;

    const auto rot = xValue * Drivetrain::kMaxAngularSpeed;
    // const auto rot = units::radians_per_second_t(0);

    frc::SmartDashboard::PutNumber("ySpeed (m/s)", double(ySpeed));
    frc::SmartDashboard::PutNumber("rot (rad/s)", double(rot));

    m_drive.Drive(ySpeed, rot);

  }

 private:
  Drivetrain m_drive;

};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
