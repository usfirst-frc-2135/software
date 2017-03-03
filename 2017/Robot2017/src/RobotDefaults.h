/*
 * RobotDefaults.h
 *
 *  Created on: Mar 1, 2017
 *      Author: PHS_User
 */

#ifndef ROBOTDEFAULTS_H_
#define ROBOTDEFAULTS_H_

//	Identify if ADXRS450 Gyro is in use by enabling this define

#define USE_ADXRS450_GYRO	// Comment out for analog Gyro or to disable

//	SmartDashboard parameters and defaults

//	SmartDashboard Autonomous command - Drive Distance

#define AUTON_DRIVEDISTANCE		"DriveDistanceInches"
#define AUTON_DRIVEDISTANCE_D	60.0	// Default value - inches

//	SmartDashboard Autonomous command - Drive Heading (Turn)

#define AUTON_DRIVEHEADING		"DriveHeadingAngle"
#define AUTON_DRIVEHEADING_D	30.0		// Default value - degrees

// SmartDashboard Chassis Turn PID values

#define	CHS_TURNPID_OUT_L		"LTurnPIDOutput"
#define CHS_TURNPID_OUT_R		"RTurnPIDOutput"

//	SmartDashboard Chassis basic configuration parameters

#define	CHS_DRIVE_DIRECTION		"Chs_DriveDirection"
#define CHS_DRIVE_SCALING		"Chs_DriveScaling"
#define CHS_DRIVE_SCALING_D		1.0
#define CHS_DRIVE_SPIN			"Chs_DriveSpin"
#define CHS_DRIVE_SPIN_D		0.4
#define CHS_DRIVE_BRAKEMODE		"Chs_DriveBrakeMode"

// SmartDashboard Chassis Distance PID configuration (Talon SRX)

#define CHS_CL_RAMPRATE			"ChsCL_RampRate"
#define	CHS_CL_RAMPRATE_D		24.0

#define CHS_CL_ALLOWERROR		"ChsCL_AllowError"
#define	CHS_CL_ALLOWERROR_D		30

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

#define	CAM_TURNRIGHT			"Cam_TurnRight"

#define	CAM_TURNANGLE			"Cam_TurnAngle"

#define	CAM_FOUNDTARGET			"Cam_FoundTarget"

#endif /* ROBOTDEFAULTS_H_ */