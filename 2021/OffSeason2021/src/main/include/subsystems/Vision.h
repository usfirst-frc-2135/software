// RobotBuilder Version: 3.1
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#pragma once

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include <frc2/command/SubsystemBase.h>

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

/**
 *
 *
 * @author ExampleAuthor
 */
class Vision : public frc2::SubsystemBase
{
private:
    // It's desirable that everything possible is private except
    // for methods that implement subsystem capabilities
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    std::shared_ptr<NetworkTable> table;

    // Declare module variables
    double m_targetHorizAngle; // Horizontal Offset from Crosshair to Target
    double m_targetVertAngle;  // Vertical Offset from Crosshair to Target
    double m_targetArea;       // Target Area (0% of image to 100% of image)
    double m_targetSkew;       // Target Skew or rotation (-90 degrees to 0 degrees)
    bool m_targetValid;        // Target Valid or not

public:
    Vision();
    void Periodic() override;
    void SimulationPeriodic() override;
    void Initialize(void);

    double GetHorizOffsetDeg();
    double GetVertOffsetDeg();
    double GetTargetArea();
    double GetTargetSkew();
    bool GetTargetValid();
    void SetLEDMode(bool mode);

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
};
