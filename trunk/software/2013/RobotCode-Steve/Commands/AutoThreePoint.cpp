// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.



#include "AutoThreePoint.h"
#include "../Commands/ShiftLowGear.h"
#include "../Commands/DriveStraightDistance.h"
#include "../Commands/DriveTrainOff.h"
#include "../Commands/AimUp.h"
#include "../Commands/ShooterRun.h"
#include "../Commands/FireReloadTimed.h"
#include "../Commands/FireFrisbeeTimed.h"

AutoThreePoint::AutoThreePoint() {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

	// To run multiple commands at the same time,
	// use AddParallel()
	// e.g. AddParallel(new Command1());
	//      AddSequential(new Command2());
	// Command1 and Command2 will run in parallel.
	AddParallel(new ShiftLowGear());
	AddSequential(new DriveStraightDistance());
	AddParallel(new DriveTrainOff());
	AddParallel(new AimUp());
	AddParallel(new ShooterRun());
	AddSequential(new FireReloadTimed());
	AddSequential(new FireFrisbeeTimed());
	AddSequential(new FireReloadTimed());
	AddSequential(new FireFrisbeeTimed());
	AddSequential(new FireReloadTimed());
	AddSequential(new FireFrisbeeTimed());
	AddSequential(new FireReloadTimed());
	AddSequential(new FireFrisbeeTimed());
	

	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.
}