/*
 * RobotDefaults.h
 *
 *  Created on: Mar 1, 2017
 *      Author: PHS_User
 */

#ifndef ROBOTDEFAULTS_H_
#define ROBOTDEFAULTS_H_

//  Identify if Crush or Brush is in use by enabling this define

#define CRUSH_SETTINGS   // Comment out for Brush settings

//	Identify if ADXRS450 Gyro is in use by enabling this define

#define USE_ADXRS450_GYRO	// Comment out for analog Gyro or to disable

//#define ROBORIO_STANDALONE	// Comment out for normal operation (talons present)

//	SmartDashboard parameters and defaults

//	SmartDashboard Autonomous command - Drive Distance

#define AUTON_DRIVEDISTANCE		"DriveDistanceInches"
#define AUTON_DRIVEDISTANCE_D	-78.6	// Default value - inches

//	SmartDashboard Autonomous command - Drive Heading (Turn)

#define AUTON_DRIVEHEADING		"DriveHeadingAngle"
#define AUTON_DRIVEHEADING_D	30.0		// Default value - degrees

// SmartDashboard Chassis Turn PID values

#define	CHS_TURNPID_OUT_L		"LTurnPIDOutput"
#define CHS_TURNPID_OUT_R		"RTurnPIDOutput"

//	SmartDashboard Chassis basic configuration parameters

#define CHS_TURN_SCALING_E 		// Leave in if high gear is scaled
#define CHS_TURN_SCALING		"Chs_TurnScaling"
#define CHS_TURN_SCALING_D		false

#define	CHS_DRIVE_DIRECTION		"Chs_DriveDirection"
#define CHS_DRIVE_BRAKEMODE		"Chs_DriveBrakeMode"

#define CHS_DRIVE_SCALING		"Chs_DriveScaling"
#define CHS_DRIVE_SCALING_D		1.0

#define CHS_DRIVE_SPIN			"Chs_DriveSpin"
#define CHS_DRIVE_SPIN_D		0.4

// SmartDashboard Chassis Distance PID configuration (Talon SRX)

#define CHS_CL_RAMPRATE			"ChsCL_RampRate"
#define	CHS_CL_RAMPRATE_D		24.0

#define CHS_CL_ALLOWERROR		"ChsCL_AllowError"
#define	CHS_CL_ALLOWERROR_D		30

#define CHS_CL_PEAKOUTVOLTS		"ChsCL_PeakOutput"
#define	CHS_CL_PEAKOUTVOLTS_D	6.0

#define CHS_CL_NOMOUTVOLTS		"ChsCL_NomOutput"
#define	CHS_CL_NOMOUTVOLTS_D	0.0

#define	CHS_CL_PROPORTIONAL		"ChsCL_Proportional"
#define	CHS_CL_PROPORTIONAL_D	3.5

#define	CHS_CL_TARGETINCHES		"ChsCL_TargetInches"
#define	CHS_CL_TARGETINCHES_D	60.0

//	SmartDashboard Chassis sensor readings

#define CHS_ENCPOSITION_L		"ChsL_EncPosition"
#define CHS_ENCPOSITION_R		"ChsR_EncPosition"

#define CHS_ROTATIONS_L			"ChsL_Rotations"
#define CHS_ROTATIONS_R			"ChsR_Rotations"

#define CHS_CL_ERROR_L			"ChsL_CLError"
#define CHS_CL_ERROR_R			"ChsR_CLError"

#define CHS_GYROANGLE			"Chs_GyroAngle"

#define CHS_CAMTURNKP			"Chs_CamTurnKP"
#define CHS_CAMTURNKP_D			0.02

//  Shooter light status

#define SHTR_LIGHT				"ShooterLight"
#define SHTR_LIGHT_D			false

//  Climber speeds for forward and low power mode

#define CLMB_SPEED				"Clmb_Speed"
#define CLMB_SPEED_D			1.0

#define CLMB_LOW_SPEED			"Clmb_Low_Speed"
#define CLMB_LOW_SPEED_D		0.2

//  SmartDashboard Camera Pipeline Toggle settings

#define CAM_VISIONPIPEON		"Cam_VisionPipe"
#define CAM_VISIONPIPEON_D		0.0

//	SmartDashboard Vision settings

#define	CAM_BRIGHTNESS			"Cam_Brightness_%"
#define CAM_BRIGHTNESS_D		0.0

#define	CAM_EXPOSURE			"Cam_Exposure_%"
#define CAM_EXPOSURE_D			0.0

#define	CAM_HUESTART			"Cam_HueStart"
#define CAM_HUESTART_D			0.0

#define	CAM_HUEEND				"Cam_HueEnd"
#define CAM_HUEEND_D			102.0

#define	CAM_SATSTART			"Cam_SatStart"
#define CAM_SATSTART_D			202.0

#define	CAM_SATEND				"Cam_SatEnd"
#define CAM_SATEND_D			255.0

#define	CAM_LUMSTART			"Cam_LumStart"
#define CAM_LUMSTART_D			24.0

#define	CAM_LUMEND				"Cam_LumEnd"
#define CAM_LUMEND_D			255.0

//	SmartDashboard Vision readout

#define	CAM_TURNANGLE			"Cam_TurnAngle"
#define	CAM_TURNANGLE_D			0.0

#define	CAM_FOUNDTARGET			"Cam_FoundTarget"

#endif /* ROBOTDEFAULTS_H_ */
