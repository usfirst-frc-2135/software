/*
 * RobotDefaults.h
 *
 *  Created on: Mar 1, 2017
 *      Author: PHS_User
 */

#ifndef ROBOTDEFAULTS_H_
#define ROBOTDEFAULTS_H_

// #define ROBORIO_STANDALONE	// Comment out for normal operation (talons present)

//	SmartDashboard parameters and defaults

// Smartdashboard Autonomous Program settings

#define AUTON_POS123MOVE			"Auto_Pos123"	// Move forward to cross auton line ~8" short of pos 2 move
#define AUTON_POS123MOVE_D		-68.8

#define AUTON_POS1_LEG1			"Auto_Pos1Leg1"	// Move forward to turning point
#define AUTON_POS1_LEG1_D		-55.4
#define AUTON_POS1_TURN			"Auto_Pos1Turn"	// Turn right 60 degrees
#define AUTON_POS1_TURN_D		60.0
#define AUTON_POS1_LEG2			"Auto_Pos1Leg2"	// Move forward toward peg 1
#define AUTON_POS1_LEG2_D		-76.0

#define AUTON_POS2_LEG1			"Auto_Pos2Leg1"	// Move forward to peg 2
#define AUTON_POS2_LEG1_D		-76.8

#define AUTON_POS3_LEG1			"Auto_Pos3Leg1"	// Move forward to turning point
#define AUTON_POS3_LEG1_D		-55.4
#define AUTON_POS3_TURN			"Auto_Pos3Turn"	// Turn left 60 degrees
#define AUTON_POS3_TURN_D		-60.0
#define AUTON_POS3_LEG2			"Auto_Pos3Leg2"	// Move forward toward peg 3
#define AUTON_POS3_LEG2_D		-76.0

//	SmartDashboard Autonomous command - Drive Heading (Turn)

#define AUTON_DRIVEHEADING		"DriveHeadingAngle"
#define AUTON_DRIVEHEADING_D		60.0				// Default value - degrees

// SmartDashboard Chassis Turn PID values

#define	CHS_TURNPID_OUT_L		"LTurnPIDOutput"
#define CHS_TURNPID_OUT_R		"RTurnPIDOutput"

//	SmartDashboard Chassis basic configuration parameters

#define CHS_TURN_SCALING			"Chs_TurnScaling"
#define CHS_TURN_SCALING_D		1.0				// 1.0 is no scaling, < 1.0 is max X output

#define	CHS_DRIVE_DIRECTION		"Chs_DriveDirection"
#define CHS_DRIVE_BRAKEMODE		"Chs_DriveBrakeMode"

#define CHS_DRIVE_SCALING		"Chs_DriveScaling"
#define CHS_DRIVE_SCALING_D		1.0				// 1.0 is full CIM speed, < 1.0 is max Y output

#define CHS_DRIVE_SPIN			"Chs_DriveSpin"
#define CHS_DRIVE_SPIN_D			0.6				// 1.0 is full speed, so slow down spin turns

#define CHS_INVERT_ENABLE 		"Chs_InvertEnable"
#define CHS_INVERT_ENABLE_D		false

// SmartDashboard Chassis Distance PID configuration (Talon SRX)

#define CHS_CL_RAMPRATESECS		"ChsCL_RampRate"
#define	CHS_CL_RAMPRATESECS_D	1.0				// Number of seconds for robot to go from stopped to full

#define CHS_CL_ALLOWERROR		"ChsCL_AllowError"
#define	CHS_CL_ALLOWERROR_D		37				// Number of encoder counts allowed from target setpoint

#define CHS_CL_PEAKOUTPCNT		"ChsCL_PeakOutput"
#define	CHS_CL_PEAKOUTPCNT_D		1.0				// 1.0 is full CIM motor output

#define CHS_CL_NOMOUTPCNT		"ChsCL_NomOutput"
#define	CHS_CL_NOMOUTPCNT_D		0.0				// 1.0 is full CIM motor output, 0.0 disables

#define	CHS_CL_PROPORTIONAL		"ChsCL_Proportional"
#define	CHS_CL_PROPORTIONAL_D	1.51				// Kp for drive PID

//	SmartDashboard Chassis sensor readings

#define CHS_ENCPOSITION_L		"ChsL_EncPosition"
#define CHS_ENCPOSITION_R		"ChsR_EncPosition"

#define CHS_CL_ERROR_L			"ChsL_CLError"
#define CHS_CL_ERROR_R			"ChsR_CLError"

#define CHS_GYROANGLE			"Chs_GyroAngle"

#define CHS_TURNKP				"Chs_TurnKP"
#define CHS_TURNKP_D				0.08				// Kp for drive turn PID

#define CHS_CAMTURNKP			"Chs_CamTurnKP"
#define CHS_CAMTURNKP_D			0.45				// Kp for camera vision turn PID

//  Shooter light status

#define SHTR_LIGHT				"ShooterLight"
#define SHTR_LIGHT_D				false

//  Climber speeds for forward and low power mode

#define CLMB_SPEED				"Clmb_Speed"
#define CLMB_SPEED_D				1.0				// Climb rate for full speed climb

#define CLMB_LOW_SPEED			"Clmb_Low_Speed"
#define CLMB_LOW_SPEED_D			0.2				// Climb rate for low speed climb

//  SmartDashboard Camera Pipeline Toggle settings

#define CAM_VISIONPIPEON			"Cam_VisionPipe"
#define CAM_VISIONPIPEON_D		0.0

//	SmartDashboard Vision settings

#define	CAM_BRIGHTNESS			"Cam_Brightness_%"
#define CAM_BRIGHTNESS_D			0.0

#define	CAM_EXPOSURE				"Cam_Exposure_%"
#define CAM_EXPOSURE_D			0.0

#define	CAM_HUESTART				"Cam_HueStart"
#define CAM_HUESTART_D			0.0

#define	CAM_HUEEND				"Cam_HueEnd"
#define CAM_HUEEND_D				102.0

#define	CAM_SATSTART				"Cam_SatStart"
#define CAM_SATSTART_D			202.0

#define	CAM_SATEND				"Cam_SatEnd"
#define CAM_SATEND_D				255.0

#define	CAM_LUMSTART				"Cam_LumStart"
#define CAM_LUMSTART_D			24.0

#define	CAM_LUMEND				"Cam_LumEnd"
#define CAM_LUMEND_D				255.0

//	SmartDashboard Vision readout

#define	CAM_TURNANGLE			"Cam_TurnAngle"
#define	CAM_TURNANGLE_D			0.0

#define CAM_DISTANCE			"Cam_Distance"
#define CAM_DISTANCE_D			0.0

#define	CAM_FOUNDTARGET			"Cam_FoundTarget"

#endif /* ROBOTDEFAULTS_H_ */
