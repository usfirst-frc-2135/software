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

	frc2135::RobotConfig* config = frc2135::RobotConfig::GetInstance();
	double	cmdDistLeg1 = 0.0;
	double	cmdDistTurn1 = 0.0;
	double	cmdDistLeg2 = 0.0;

	config->GetValueAsDouble("AutoPos1ScaleLeg1", cmdDistLeg1, 261.5);
	config->GetValueAsDouble("AutoPos1ScaleTurn1", cmdDistTurn1, 45.0);
	config->GetValueAsDouble("AutoPos1ScaleLeg2", cmdDistLeg2, 11.61);

	std::printf("2135: Auto Pos 1 Scale - Init Leg1 %4.2f in, Turn1 %4.1f deg, Leg2 %4.2f in\n",
	cmdDistLeg1, cmdDistTurn1, cmdDistLeg2);

	AddParallel(new GripperRun(Robot::gripper->GRIPPER_HOLD));		// Gripper should hold cube (instantaneous)
	AddParallel(new ElevatorRun(Robot::elevator->SWITCH_HEIGHT));	// Elevator to switch height - takes about 1 sec
	AddParallel(new WristRun(Robot::wrist->WRIST_DELIVER)); 		// Wrist ready to deliver angle < 1 sec
	AddSequential(new AutoDriveDist(cmdDistLeg1));  				// Drive to the turn

																	// Gripper still holding
																	// Elevator still at switch height
																	// Wrist still at deliver angle
	AddSequential(new AutoDriveTurn(cmdDistTurn1));					// Drive turn to aim at scale

																	// Gripper still holding
																	// Elevator still at switch height
																	// Wrist still at deliver angle
	AddSequential(new AutoDriveDist(cmdDistLeg2));					// Drive up to the scale

	AddSequential(new ElevatorRun(Robot::elevator->SCALE_HI_HEIGHT)); // Raise to scale position
																	// This will cause drivetrain motor safety help messages

	AddParallel(new GripperRun(Robot::gripper->GRIPPER_REVERSE));	// Expel cube (instantaneous)
																	// Elevator still at switch height
																	// Wrist still deliver level
	AddSequential(new AutoStop(), 1.0);								// Tell drive motors to explicitly stop for 1 second

	AddParallel(new GripperRun(Robot::gripper->GRIPPER_STOP));		// Stop gripper
	AddParallel(new ElevatorRun(Robot::elevator->SWITCH_HEIGHT)); 	// Lower to switch position
	AddSequential(new AutoStop());									// Tell drive motors to explicitly stop


              // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=COMMAND_DECLARATIONS
              // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=COMMAND_DECLARATIONS
 }
