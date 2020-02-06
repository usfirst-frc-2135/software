/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivetrain.h"

void Drivetrain::SetSpeeds(const frc::DifferentialDriveWheelSpeeds& speeds) {
  const auto leftOutput = m_leftPIDController.Calculate(
      GetSpeed(&m_leftMaster), speeds.left.to<double>());
  const auto rightOutput = m_rightPIDController.Calculate(
      GetSpeed(&m_rightMaster), speeds.right.to<double>());

  m_leftGroup.Set(leftOutput);
  m_rightGroup.Set(rightOutput);
  std::printf("leftOutput", m_leftMaster.GetMotorOutputPercent());
  std::printf("rightOutput", m_rightMaster.GetMotorOutputPercent());
  std::printf("");
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