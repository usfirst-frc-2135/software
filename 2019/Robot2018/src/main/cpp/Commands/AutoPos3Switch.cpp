// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.



#include "Commands/AutoPos3Switch.h"
#include "Commands/ElevatorRun.h"
#include "Commands/WristRun.h"
#include "Commands/AutoDriveDist.h"
#include "Commands/AutoDriveTurn.h"
#include "Commands/GripperRun.h"
#include "Commands/AutoStop.h"

#include "RobotDefaults.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

AutoPos3Switch::AutoPos3Switch() {
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
	frc2135::RobotConfig* config = frc2135::RobotConfig::GetInstance();
	double	cmdDistLeg1 = 0.0;
	double	cmdDistTurn1 = 0.0;
	double	cmdDistLeg2 = 0.0;

	config->GetValueAsDouble("AutoPos3SwitchLeg1", cmdDistLeg1, 145.25);
	config->GetValueAsDouble("AutoPos3SwitchTurn1", cmdDistTurn1, -90.0);
	config->GetValueAsDouble("AutoPos3SwitchLeg2", cmdDistLeg2, 18.0);

	std::printf("2135: Auto Pos 3 Switch -  Init Leg1 %4.2f in, Turn1 %4.1f deg, Leg2 %4.2f in\n",
			cmdDistLeg1, cmdDistTurn1, cmdDistLeg2);

	AddParallel(new GripperRun(Robot::gripper->GRIPPER_HOLD));		// Gripper should hold cube (instantaneous)
	AddParallel(new ElevatorRun(Robot::elevator->SWITCH_HEIGHT));	// Elevator to switch height - takes about 1 sec
	AddParallel(new WristRun(Robot::wrist->WRIST_DELIVER)); 		// Wrist ready to deliver angle < 1 sec
	AddSequential(new AutoDriveDist(cmdDistLeg1)); 					// Drive to the turning point - about 1 sec

																	// Gripper still holding
																	// Elevator still at switch height
																	// Wrist still at deliver angle
	AddSequential(new AutoDriveTurn(cmdDistTurn1));					// Drive turn to aim at switch - < 1 sec

																	// Gripper still holding
																	// Elevator still at switch height
	AddParallel(new WristRun(Robot::wrist->WRIST_FLAT));			// Wrist to flat level < 1 sec
	AddSequential(new AutoDriveDist(cmdDistLeg2));					// Drive to switch < 1 sec

	AddParallel(new GripperRun(Robot::gripper->GRIPPER_REVERSE));	// Expel cube (instantaneous)
																	// Elevator still at switch height
																	// Wrist still flat level
	AddSequential(new AutoStop(), 1.0);								// Tell drive motors to explicitly stop for 1 second

	AddParallel(new GripperRun(Robot::gripper->GRIPPER_STOP));		// Stop gripper
	AddSequential(new AutoStop());									// Tell drive motors to explicitly stop

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=COMMAND_DECLARATIONS
     // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=COMMAND_DECLARATIONS
 }
