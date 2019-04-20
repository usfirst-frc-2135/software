/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "frc2135/GripVisionLoop.h"
#include <networktables/NetworkTableInstance.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

//	OnBoard Vision processing
GripVisionLoop::GripVisionLoop() {

	///////////////////////////
	// Set up Network Tables
 	nt::NetworkTableInstance ntinst = nt::NetworkTableInstance::GetDefault();
    // Default is 10 Hz, increase to 100 Hz
	ntinst.SetUpdateRate(0.01);
	// Get/Create a Vision Network Table
	std::shared_ptr<nt::NetworkTable>  table = ntinst.GetTable("Vision");
	nt::NetworkTableEntry camConnected = table->GetEntry("Connected");
	camConnected.SetBoolean(false);
	nt::NetworkTableEntry tickEntry = table->GetEntry("Ticks");
	nt::NetworkTableEntry goalDistEntry = table->GetEntry("GoalDist");
	nt::NetworkTableEntry goalYawAngleEntry = table->GetEntry("GoalYawAngle");
	nt::NetworkTableEntry goalFaceAngleEntry = table->GetEntry("GoalFaceAngle");
	double ticks = 0.0;

	///////////////////////////
	// Set up camera
	struct pixelRect
	{ 			// Vision frame rectangle of pixels
		int width;
		int height;
	};

	// Camera - Microsoft LifeCam
	struct pixelRect res = { 320, 240 };
	const int fps = 15;
	const int brightness = 50;
	const int exposure = 50;

	// Start the camera server
	const std::string defCamName = "USBCAM";
	cs::UsbCamera	cam = frc::CameraServer::GetInstance()->StartAutomaticCapture(defCamName, 0);
	std::string		camName = cam.GetName();

	double	startTime = frc::GetTime();

	// Wait up to 3.0 seconds for camera server to detect
	while (!cam.IsConnected() && ((frc::GetTime() - startTime) < 3.0)) {
		std::printf("2135: CAM Waiting for camera to connect %5.3f\n", frc::GetTime() - startTime);
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}

	std::printf("2135: CAM Camera Name %s\n", cam.GetName().c_str());
	std::printf("2135: CAM Camera Desc %s\n", cam.GetDescription().c_str());
	std::printf("2135: CAM Camera Path %s\n", cam.GetPath().c_str());

	if (cam.IsConnected()) {
		camConnected.SetBoolean(true);
		std::printf("2135: CAM Camera is CONNECTED\n");
		std::printf("2135: CAM Camera data rate %5.1f\n", cam.GetActualDataRate());
		std::printf("2135: CAM Camera FPS       %5.1f\n", cam.GetActualFPS());
	}
	else {
		std::printf("2135: ERROR: CAM Camera is NOT CONNECTED\n");
		std::printf("2135: CAM Camera removal %s\n", cam.GetDescription().c_str());
		frc::CameraServer::GetInstance()->RemoveCamera(defCamName);
		// Not connected - nothing left to do here
		return;
	}

	std::printf("2135: Configure camera - %d x %d, %d fps, %d bright, %d expos\n",
		res.width, res.height, fps, brightness, exposure);
	if (!cam.SetVideoMode(cs::VideoMode::kMJPEG, res.width, res.height, fps))
		std::printf("2135: Cam resolution/fps not set - %d\n", cam.GetLastStatus());
	cam.SetBrightness(brightness);
	if (cam.GetLastStatus() != 0)
		std::printf("2135: Cam Brightness not set - %d\n", cam.GetLastStatus());
	cam.SetExposureManual(exposure);
	if (cam.GetLastStatus() != 0)
		std::printf("2135: Cam Exposure not set - %d\n", cam.GetLastStatus());

	///////////////////////////
	// Set up processed output video
	cs::CvSource outStream;
	outStream = frc::CameraServer::GetInstance()->PutVideo("Goal Video", res.width, res.height);

	///////////////////////////
	// Set up pipeline processing
	grip::GripOuterPipeline *gripPipe = new grip::GripOuterPipeline();
	bool	goalFound = false;
    double  goalDist = 0.0;
    double  goalFaceAngle = 0.0;
    double  goalYawAngle = 0.0;

	frc::SmartDashboard::PutBoolean(CAM_FOUNDTARGET, goalFound);

	///////////////////////////
	// Run vision thread
    std::thread([&] {
		// something like this for GRIP:
		frc::VisionRunner<grip::GripOuterPipeline> 
			runner(cam, gripPipe, [&](grip::GripOuterPipeline& listener) {

				// Take goal data and put  into NT values
				gripPipe->GetGoalHatch(&goalDist, &goalYawAngle, &goalFaceAngle);
				goalDistEntry.SetDouble(goalDist);
				goalYawAngleEntry.SetDouble(goalYawAngle);
				goalFaceAngleEntry.SetDouble(goalFaceAngle);
				tickEntry.SetDouble(ticks);
				ticks += 1/fps;

				// Update SmartDashboard for use by PID controller
				frc::SmartDashboard::PutBoolean(CAM_FOUNDTARGET, goalFound);
				frc::SmartDashboard::PutNumber(CAM_DISTANCE, goalDist);
				frc::SmartDashboard::PutNumber(CAM_TURNANGLE, goalYawAngle);
				frc::SmartDashboard::PutNumber(CAM_FACEANGLE, goalFaceAngle);
				frc::SmartDashboard::PutNumber("CAM_TICKS", ticks);

				// Add goals to video frame
				//outStream.PutFrame(outFrame);
		} );
		runner.RunForever();
    } ).detach();
}
