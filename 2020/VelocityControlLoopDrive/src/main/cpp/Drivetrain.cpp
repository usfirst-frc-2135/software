/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivetrain.h"
#include <frc/SmartDashboard/SmartDashboard.h>

void Drivetrain::SetSpeeds(const frc::DifferentialDriveWheelSpeeds& speeds)
{
  // calculates FF output
  const auto leftFeedforward = m_feedforward.Calculate(speeds.left);
  const auto rightFeedforward = m_feedforward.Calculate(speeds.right);
  double leftSpeed = GetSpeed(&m_leftMaster);
  double rightSpeed = GetSpeed(&m_rightMaster);
  double leftSpeedPassed = speeds.left.to<double>();
  double rightSpeedPassed = speeds.right.to<double>();
  // calculates PID output
  const auto leftOutput = m_leftPIDController.Calculate(
      leftSpeed, leftSpeedPassed);
  const auto rightOutput = m_rightPIDController.Calculate(
      rightSpeed, rightSpeedPassed);

  // Divide FF by 12 to normalize to the same units as the outputs
  double leftTotalOutput = -leftOutput - double(leftFeedforward) / 12.0;
  double rightTotalOutput = rightOutput + double(rightFeedforward) / 12.0;
  m_leftMaster.Set(leftTotalOutput);
  m_rightMaster.Set(rightTotalOutput);

  //frc::SmartDashboard::PutNumber("leftOutput", -leftOutput);
  //frc::SmartDashboard::PutNumber("rightOutput", rightOutput);
  frc::SmartDashboard::PutNumber("leftFF", double(leftFeedforward) / 12.0);
  frc::SmartDashboard::PutNumber("rightFF", double(rightFeedforward) / 12.0);
  frc::SmartDashboard::PutNumber("leftTotalOutput", leftTotalOutput);
  frc::SmartDashboard::PutNumber("rightTotalOutput", rightTotalOutput);
  frc::SmartDashboard::PutNumber("leftSpeed", leftSpeed);
  frc::SmartDashboard::PutNumber("rightSpeed", rightSpeed);
  frc::SmartDashboard::PutNumber("speed difference", rightSpeed - leftSpeed);
  frc::SmartDashboard::PutNumber("Output difference", rightOutput - leftOutput);
  frc::SmartDashboard::PutNumber("left encoder", m_leftMaster.GetSelectedSensorPosition());
  frc::SmartDashboard::PutNumber("right encoder", m_rightMaster.GetSelectedSensorPosition());

}

void Drivetrain::Drive(units::meters_per_second_t ySpeed, units::radians_per_second_t rot)
{
  SetSpeeds(m_kinematics.ToWheelSpeeds( { ySpeed, 0_mps, rot } ));
}

void Drivetrain::UpdateOdometry()
{
  m_odometry.Update(GetAngle(), units::meter_t(GetDistance(&m_leftMaster)), units::meter_t(GetDistance(&m_rightMaster)));
}

double Drivetrain::GetDistance(WPI_TalonSRX *talon)
{
  return kEncoderDistancePerPulse * talon->GetSelectedSensorPosition();
}

double Drivetrain::GetSpeed(WPI_TalonSRX *talon)
{
  return kEncoderDistancePerPulse * (talon->GetSelectedSensorVelocity() * 10);
}
