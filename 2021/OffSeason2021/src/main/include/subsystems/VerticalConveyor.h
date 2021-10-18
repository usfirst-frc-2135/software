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
#include "ctre/Phoenix.h"

#include <frc2/command/SubsystemBase.h>

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

/**
 *
 *
 * @author ExampleAuthor
 */
class VerticalConveyor : public frc2::SubsystemBase
{
private:
    // It's desirable that everything possible is private except
    // for methods that implement subsystem capabilities
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    WPI_TalonSRX m_motorVC9{ 9 };

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    // Declare constants
    const int m_conveyorDebug = 0; // DEBUG flag to disable/enable extra logging calls
    const int kCANTimeout = 10;    // CAN timeout in msec to wait for response

    // Declare module variables
    bool m_talonValidVC9; // Health indicator for vertical conveyor talon
    double m_acquireSpeed;
    double m_expelSpeed;
    double m_expelSpeedFast;

public:
    VerticalConveyor();

    void Periodic() override;
    void SimulationPeriodic() override;
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    //Vertical conveyor motor control states
    typedef enum conveyorDir_e
    {
        VCONVEYOR_STOP = 0,
        VCONVEYOR_ACQUIRE = 1,
        VCONVEYOR_EXPEL = -1,
        VCONVEYOR_EXPEL_FAST = -2
    } conveyorDir_e;

    void Initialize(void);
    void FaultDump(void);

    void SetVerticalConveyorSpeed(int mode);
};
