/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "frc2135/VisionThread.h"
#include <networktables/NetworkTableInstance.h>
#include "cameraserver/CameraServer.h"

///////////////////////////////////////////////////////////////////////////////////////////////////

//	OnBoard Vision processing
VisionThread::VisionThread() {

    ///////////////////////////
    // Run vision thread
    std::thread([&] {
        std::printf("2135: VisionThread Constructor\n");

        ///////////////////////////
        // Set up Network Tables
        nt::NetworkTableInstance ntinst = nt::NetworkTableInstance::GetDefault();
        // Default is 10 Hz, increase to 100 Hz
        ntinst.SetUpdateRate(0.01);
        // Get/Create a Vision Network Table
        bool goalFound = false;
        double goalDist = 0.0;
        double goalYawAngle = 0.0;
        double goalFaceAngle = 0.0;
        double ticks = 0.0;

        std::shared_ptr<nt::NetworkTable> table = ntinst.GetTable("Vision");
        nt::NetworkTableEntry camConnected = table->GetEntry("Connected");
        nt::NetworkTableEntry tickEntry = table->GetEntry("Ticks");
        nt::NetworkTableEntry goalDistEntry = table->GetEntry("GoalDist");
        nt::NetworkTableEntry goalYawAngleEntry = table->GetEntry("GoalYawAngle");
        nt::NetworkTableEntry goalFaceAngleEntry = table->GetEntry("GoalFaceAngle");

        ///////////////////////////
        // Set up camera
        struct pixelRect {      // Vision frame rectangle of pixels
            int width;
            int height;
        };

        // Camera - Microsoft LifeCam
        struct pixelRect res = {320, 240};
        const int fps = 8;
        const int brightness = 0;
        const int exposure = 0;

        // Start the camera server
        const std::string defCamName = "USBCAM";
        cs::UsbCamera m_cam = frc::CameraServer::GetInstance()->StartAutomaticCapture(defCamName, 0);

        double startTime = frc::GetTime();
        camConnected.SetBoolean(false);

        // Wait up to 3.0 seconds for camera server to detect
        while (!m_cam.IsConnected() && ((frc::GetTime() - startTime) < 3.0)) {
            std::printf("2135: CAM Waiting for camera to connect %5.3f\n", frc::GetTime() - startTime);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }

        std::printf("2135: CAM Camera Name %s\n", m_cam.GetName().c_str());
        std::printf("2135: CAM Camera Desc %s\n", m_cam.GetDescription().c_str());
        std::printf("2135: CAM Camera Path %s\n", m_cam.GetPath().c_str());

        if (m_cam.IsConnected()) {
            camConnected.SetBoolean(true);
            std::printf("2135: CAM Camera is CONNECTED\n");
            std::printf("2135: CAM Camera data rate %5.1f\n", m_cam.GetActualDataRate());
            std::printf("2135: CAM Camera FPS       %5.1f\n", m_cam.GetActualFPS());
        }
        else {
            std::printf("2135: ERROR: CAM Camera is NOT CONNECTED\n");
            std::printf("2135: CAM Camera removal %s\n", m_cam.GetDescription().c_str());
            frc::CameraServer::GetInstance()->RemoveCamera(defCamName);
            return; // Not connected - nothing left to do here
        }

        std::printf("2135: Configure camera - %d x %d, %d fps, %d bright, %d expos\n",
                    res.width, res.height, fps, brightness, exposure);
        if (!m_cam.SetVideoMode(cs::VideoMode::kMJPEG, res.width, res.height, fps))
            std::printf("2135: WARNING: Cam resolution/fps not set - %d\n", m_cam.GetLastStatus());
        m_cam.SetBrightness(brightness);
        if (m_cam.GetLastStatus() != 0)
            std::printf("2135: WARNING: Cam Brightness not set - %d\n", m_cam.GetLastStatus());
        m_cam.SetExposureManual(exposure);
        if (m_cam.GetLastStatus() != 0)
            std::printf("2135: WARNING: Cam Exposure not set - %d\n", m_cam.GetLastStatus());

        ///////////////////////////
        // Creates the CvSink and connects it to the UsbCamera
        cs::CvSink m_cvSink = frc::CameraServer::GetInstance()->GetVideo();
        cs::CvSource m_cvSource = frc::CameraServer::GetInstance()->PutVideo("Goal Video", res.width, res.height);
        cv::Mat m_sourceMat;

        grip::VisionOuterPipeline *gripPipe = new grip::VisionOuterPipeline();

        //////////////////////////
        //  The Vision thread
        while (true) {

            tickEntry.SetDouble(ticks);
            goalDistEntry.SetDouble(goalDist);
            goalYawAngleEntry.SetDouble(goalYawAngle);
            goalFaceAngleEntry.SetDouble(goalFaceAngle);

            frc::SmartDashboard::PutBoolean(CAM_FOUNDGOAL, goalFound);
            frc::SmartDashboard::PutNumber(CAM_TICKS, ticks);

            int validFrame = m_cvSink.GrabFrameNoTimeout(m_sourceMat);

            if ((validFrame == 0) || (m_sourceMat.empty())) {
                std::string error = m_cvSink.GetError();
                frc::DriverStation::ReportError(error);
                std::printf("2135: WARNING: Missed vision frame\n");
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                continue;
            }

            // Run vision processing gripPipe generated from GRIP
            gripPipe->Process(m_sourceMat);

            // Take goal data and put  into NT values
            goalFound = gripPipe->GetGoalHatch(&goalDist, &goalYawAngle, &goalFaceAngle);
            goalDistEntry.SetDouble(goalDist);
            goalYawAngleEntry.SetDouble(goalYawAngle);
            goalFaceAngleEntry.SetDouble(goalFaceAngle);
            ticks = ticks + (1.0 / fps);

            m_sourceMat = *gripPipe->GetSourceMat();
            m_cvSource.PutFrame(m_sourceMat);
        }
    })
        .detach();
}

VisionThread::~VisionThread() {
    std::printf("2135: VisionThread deconstructor\n");
}
