// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.



#include "AutonPos3DeliverGear.h"
#include "AutonDriveDistance.h"
#include "AutonDrivePeg3Turn.h"
#include "AutonDrivePegVision.h"
#include "AutonDelay.h"


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

AutonPos3DeliverGear::AutonPos3DeliverGear() {
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
	printf("2135: Auton Pos 3 Deliver Gear - Constructor\n");

	double	leg1 = Robot::LoadPreferencesVariable(AUTON_POS3_LEG1, AUTON_POS3_LEG1_D);
	// TODO: leg2 should be passed into AutonDrivePegVision as a default distance!
	// double	leg2 = Robot::LoadPreferencesVariable(AUTON_POS3_LEG2, AUTON_POS3_LEG2_D);

              // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=COMMAND_DECLARATIONS
                AddSequential(new AutonDriveDistance(leg1));
        AddSequential(new AutonDrivePeg3Turn());
        AddSequential(new AutonDelay(1.0));
        AddSequential(new AutonDrivePegVision());
    //    AddSequential(new AutonDriveDistance(leg2));
              // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=COMMAND_DECLARATIONS
 }
