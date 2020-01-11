/*
 * Limelight.cpp
 *
 *  Created on: Feb 2, 2019
 */

#include "frc2135/Limelight.h"

namespace frc2135 {

Limelight::Limelight() {
}

Limelight::~Limelight() {    

}

void Limelight::ReadData() {
    double targetOffsetAngle_Horizontal = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx", 0.0);;
    double targetOffsetAngle_Vertical = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ty", 0.0);
    double targetArea = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ta", 0.0);
    double targetSkew = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ts", 0.0);

    std::printf("2135: Angle_H %5.2f, Angle_V %5.2f, Area %5.2f, Skew %5.2f\n", targetOffsetAngle_Horizontal, 
        targetOffsetAngle_Vertical, targetArea, targetSkew);
}

void Limelight::SetStream() {
    // NetworkTableInstance.getDefault().getTable("limelight").getEntry("stream").setNumber(0);
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("stream", 0);
}

}