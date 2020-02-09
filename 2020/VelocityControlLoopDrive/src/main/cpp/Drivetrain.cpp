/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivetrain.h"

void Drivetrain::SetSpeeds(const frc::DifferentialDriveWheelSpeeds& speeds) {
  double leftSpeed = GetSpeed(&m_leftMaster);
  double rightSpeed = GetSpeed(&m_rightMaster);
  const auto leftOutput = m_leftPIDController.Calculate(
      leftSpeed, speeds.left.to<double>());
  const auto rightOutput = m_rightPIDController.Calculate(
      rightSpeed, speeds.right.to<double>());

  m_leftGroup.Set(-leftOutput);
  m_rightGroup.Set(rightOutput);
  int count = 0;
  if (count % 5 == 0) {
    /*std::printf("count: %i\n", count);
    std::printf("leftOutput: %f\n", leftOutput);
    std::printf("rightOutput: %f\n", rightOutput);
    std::printf("left Motor Output: %f\n", m_leftMaster.GetMotorOutputPercent());
    std::printf("right Motor Output: %f\n", m_rightMaster.GetMotorOutputPercent());
    std::printf("left Speed: %f\n", leftSpeed);
    std::printf("right Speed: %f\n", rightSpeed);
    std::printf("\n"); */
    std::printf("leftOutput: %f\n", leftOutput);
    std::printf("left Speed: %f\n", leftSpeed);
    std::printf("speeds.left: %f\n", speeds.left.to<double>());
    std::printf("speeds.right: %f\n", speeds.right.to<double>());
    std::printf("rightOutput: %f\n", rightOutput);
    std::printf("right Speed: %f\n", rightSpeed);
    std::printf("\n");
  }
  count++;
  
}

void Drivetrain::Drive(units::meters_per_second_t xSpeed,
                       units::radians_per_second_t rot) {
  SetSpeeds(m_kinematics.ToWheelSpeeds({xSpeed, 0_mps, rot}));
  
}

void Drivetrain::UpdateOdometry() {
  m_odometry.Update(GetAngle(), units::meter_t(GetDistance(&m_leftMaster)),
                    units::meter_t(GetDistance(&m_rightMaster)));
}

double Drivetrain::GetDistance(WPI_TalonSRX *talon) {
  return kEncoderDistancePerPulse * talon->GetSelectedSensorPosition();
}

double Drivetrain::GetSpeed(WPI_TalonSRX *talon) {
  return kEncoderDistancePerPulse * (talon->GetSelectedSensorVelocity() * 10);

}