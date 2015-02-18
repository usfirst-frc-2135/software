// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.



#include "AutoContainerSet.h"
#include "Commands/DriveDistance.h"
#include "Commands/DriveTurn.h"
#include "Commands/IntakeHold.h"
#include "Commands/IntakeRelease.h"
#include "Commands/ElevatorMoveToPosition.h"

AutoContainerSet::AutoContainerSet() {
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

	printf("2135: Auto Container Set\n");
	Preferences* pref = Preferences::GetInstance();
	double driveToFirstContainerDistance = pref->GetDouble("AutoContainerSetFirstDistance", 15.0);
	double driveToAutoZoneFirstDistance = pref->GetDouble("AutoContainerSetAutoZoneFirstDistance", 96.0);
	double driveTurnToNextContainer = pref->GetDouble("AutoContainerSpinLeftDegrees",144.3);
	double driveToSecondContainerDistance = pref->GetDouble("AutoContainerSetSecondDistance", 119.0);
	double driveTurnToAutoZoneSecondDegrees = pref->GetDouble("AutoContainerSetAutoZoneSecondDegrees", 144.3);
	double driveToAutoZoneSecondDistance = pref->GetDouble("AutoContainerSetAutoZoneSecondDistance", 96);

	AddSequential(new IntakeRelease());
	AddSequential(new DriveDistance(driveToFirstContainerDistance)); // Drive forward to container
	AddSequential(new IntakeHold()); 				// Grab the container
	AddSequential(new ElevatorMoveToPosition()); 	// Lift the container
	AddSequential(new DriveDistance(driveToAutoZoneFirstDistance)); // Drive forward to auto zone
	AddSequential(new ElevatorMoveToPosition()); 	// Drop the container
	AddSequential(new IntakeRelease()); 			// Release the container
	AddSequential(new DriveTurn(driveTurnToNextContainer)); // Aiming robot to next container
	AddSequential(new DriveDistance(driveToSecondContainerDistance)); // Drive forward to next container
	AddSequential(new IntakeHold()); 				// Grab container
	AddSequential(new ElevatorMoveToPosition()); 	//Lift container
	AddSequential(new DriveTurn(driveTurnToAutoZoneSecondDegrees)); // Aim to move to auto zone
	AddSequential(new DriveDistance(driveToAutoZoneSecondDistance)); // Drive forward to auto zone

}
