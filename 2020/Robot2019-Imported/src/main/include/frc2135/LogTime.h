/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

namespace frc2135 {

class LogTime {
 public:
  LogTime();
  virtual ~LogTime();

  void LogStart(void);
  void LogStop(void);

  private:
  
};

} /* namespace frc2135 */
