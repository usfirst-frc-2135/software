// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.



#include "AutoPos1Scale.h"
#include "Commands/ElevatorRun.h"
#include "Commands/WristRun.h"
#include "Commands/AutoDriveDist.h"
#include "Commands/AutoDriveTurn.h"
#include "Commands/GripperRun.h"
#include "Commands/AutoStop.h"

#include "../RobotDefaults.h"


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

AutoPos1Scale::AutoPos1Scale() {
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR
     // Add Commands here:
    // e.g. AddSequential(new Command1());
    //      AddSequential(new Command2());
    // these will run in order.

    // To run multiple commands at the same time,
    // use AddParallel()
    // e.g. AddParallel(new Command1());
    //      AddSequential(new Command2());
    // Command1 and Command2 will run in parallel.

    // A command group will require all of the subsystems that each member
    // would require.
    // e.g. if Command1 requires chassis, and Command2 requires arm,
    // a CommandGroup containing them would require both the chassis and the
    // arm.

	RobotConfig* config = RobotConfig::GetInstance();
	double	cmdDistLeg1;
	double	cmdDistTurn1;
	double	cmdDistLeg2;

	config->GetValueAsDouble("AutoPos1ScaleLeg1", cmdDistLeg1, 304.5);
	config->GetValueAsDouble("AutoPos1ScaleTurn1", cmdDistTurn1, 90.0);
	config->GetValueAsDouble("AutoPos1ScaleLeg2", cmdDistLeg2, 5.5);

	std::string	alliSwitch;
	std::printf("2135: Auto Pos 1 Scale - Init Leg1 %4.2f in, Turn1 %4.1f deg, Leg2 %4.2f in\n",
	cmdDistLeg1, cmdDistTurn1, cmdDistLeg2);

	AddParallel(new ElevatorRun(1));				// Raise to switch position
	AddParallel(new WristRun(0));					// Ready to Deliver - Flat
	AddSequential(new AutoDriveDist(cmdDistLeg1));  // Drive to the turn

	AddSequential(new AutoDriveTurn(cmdDistTurn1)); // Turn

	AddSequential(new AutoDriveDist(cmdDistLeg2));	// Drive up to the scale

	AddSequential(new ElevatorRun(3));				// Raise to scale position

	AddParallel(new GripperRun(-1));				// Expel cube
	AddSequential(new AutoStop());					// Tell motors to explicitly stop

              // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=COMMAND_DECLARATIONS
              // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=COMMAND_DECLARATIONS
 }
