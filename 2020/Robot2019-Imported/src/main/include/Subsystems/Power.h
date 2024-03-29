// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef POWER_H
#define POWER_H
#include <frc/commands/Subsystem.h>
#include <frc/commands/Command.h>
#include <frc/PowerDistributionPanel.h>

#include "RobotDefaults.h"
#include "frc2135/RobotConfig.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Power: public frc::Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<frc::PowerDistributionPanel> pdp;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	int	m_powerDebug = 0;			// Debug flag to disable extra logging calls

public:
	Power();
	void InitDefaultCommand() override;
	void Periodic() override;
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

	void Initialize(void);
	void FaultDump(void);

};

#endif
