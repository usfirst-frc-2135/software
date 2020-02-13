/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivetrain.h"
#include <frc/SmartDashboard/SmartDashboard.h>

void Drivetrain::SetSpeeds(const frc::DifferentialDriveWheelSpeeds& speeds) {
  const auto leftFeedforward = m_feedforward.Calculate(speeds.left);
  const auto rightFeedforward = m_feedforward.Calculate(speeds.right);
  double leftSpeed = GetSpeed(&m_leftMaster);
  double rightSpeed = GetSpeed(&m_rightMaster);
  double leftSpeedPassed = speeds.left.to<double>();
  double rightSpeedPassed = speeds.right.to<double>();
  const auto leftOutput = m_leftPIDController.Calculate(
      leftSpeed, leftSpeedPassed);
  const auto rightOutput = m_rightPIDController.Calculate(
      rightSpeed, rightSpeedPassed);

  m_leftMaster.Set(-leftOutput - double(leftFeedforward)); //Set sets a speed between -1.0 to 1.0
  m_rightMaster.Set(rightOutput + double(rightFeedforward)); 
  std::printf("leftOutput %f\n", -leftOutput);
  std::printf("rightOutput %f\n", rightOutput);
  std::printf("leftFF %f\n", leftFeedforward);
  std::printf("rightFF %f\n", rightFeedforward);

  // m_leftMaster.SetVoltage(units::volt_t{leftOutput} + leftFeedforward);
  // m_rightMaster.SetVoltage(units::volt_t{rightOutput} + rightFeedforward);
  frc::SmartDashboard::PutNumber("leftOutput", -leftOutput);
  frc::SmartDashboard::PutNumber("rightOutput", rightOutput);
  frc::SmartDashboard::PutNumber("leftFF", double(leftFeedforward));
  frc::SmartDashboard::PutNumber("rightFF", double(rightFeedforward));
  // frc::SmartDashboard::PutNumber("left Voltage", double(units::volt_t{leftOutput} + leftFeedforward));
  // frc::SmartDashboard::PutNumber("right Voltage", double(units::volt_t{rightOutput} + rightFeedforward));
  // std::printf("leftOutput %f\n", leftOutput);
  // std::printf("rightOutput %f\n", rightOutput);
  // std::printf("leftSpeed %f\n", leftSpeed); 
  // std::printf("speeds.left %f\n", leftSpeedPassed);
  // std::printf("rightSpeed %f\n", rightSpeed);
  // std::printf("speeds.right %f\n", rightSpeedPassed);

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
  //returns a velocity in meters per second
  return kEncoderDistancePerPulse * (talon->GetSelectedSensorVelocity() * 10);

}