/*
 * VisionThread.cpp
 *
 *  Created on: Aug 6, 2017
 *      Author: PHS_User
 */

#include <cameraserver/CameraServer.h>
#include <frc/DriverStation.h>
#include <opencv/cv.h>

#include "frc2135/VisionLoop.h"
#include "frc2135/GripContoursPipeline.h"

typedef enum { VISIONPIPE_UNINIT, VISIONPIPE_OFF, VISIONPIPE_GEAR, VISIONPIPE_SHOOTER } pipeConfig;
static	pipeConfig s_visionPipe = VISIONPIPE_OFF;

VisionLoop::VisionLoop() {
	std::printf("2135: VisionLoop Constructor\n");
}

VisionLoop::~VisionLoop() {
	// Auto-generated destructor stub
}

void VisionLoop::Run() {

	std::printf("2135: VisionLoop Run\n");

	m_res.width = 320;							// Camera Resolution setting in pixels
	m_res.height = 240;
	m_targSize.width = 3.3771;					// 2019 Vision target dimensions
	m_targSize.height = 5.8256;
	m_hatchSize.width = 14.69;					// 2019 Hatch (two targets) dimensions
	m_hatchSize.height = 5.8256;

	// CameraServer structures for processing vision frames
	cs::CvSink inStream;
	cs::CvSource outStream;
	std::unique_ptr<grip::GripContoursPipeline> gripPipe;

	// OpenCV structures for processing vision frames
	cv::Mat inFrame;
	cv::Mat gripFrame;

	// Image processing structures for identifying targets and hatches
	std::vector<std::vector<cv::Point>> *contours;
	std::vector<cv::Rect> boundingRects;
	std::vector<tData> rawData;
	std::vector<tData> validTargets;
	std::vector<tData> validHatches;
	tData goal;

	// Get initial settings from SmartDashboard
	InitializeSmartdashboard();

	// Our camera input source - start it up and configure settings
	cs::UsbCamera cam = frc::CameraServer::GetInstance()->StartAutomaticCapture();
	SetCamConfig(cam);

	// Start our GRIP-generated vision processing pipeline
	gripPipe.reset(new grip::GripContoursPipeline());

	// Set our input/output stream - available to the dashboard (same resolution as input)
	inStream = frc::CameraServer::GetInstance()->GetVideo();
	outStream = frc::CameraServer::GetInstance()->PutVideo("Contours Video", m_res.width, m_res.height);

	// Main loop for our vision thread
	while (true) {
		SetCamConfig(cam);
		int validFrame = inStream.GrabFrame(inFrame, 1000);

		// std::string imgFileName = "/home/lvuser/deploy/CargoTest24.jpg";
		// inFrame = cv::imread(imgFileName.c_str(), CV_LOAD_IMAGE_COLOR);
		// int validFrame = 1;

		if ((validFrame == 0) || (inFrame.empty())) {
		    std::string error = inStream.GetError();
		    frc::DriverStation::ReportError(error);
		    std::printf("2135: Missed frame\n");
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
		    continue;
		}
		else {
			// Run vision processing gripPipe generated from GRIP
			gripPipe->Process(inFrame);
			gripFrame = *(gripPipe->gethslThresholdOutput());
			contours = gripPipe->getfilterContoursOutput();

			ConvertContoursToBoundingRects(contours, &rawData);
			ConvertBoundingRectsToValidTargets(&rawData, &validTargets);
			ConvertValidTargetsToValidHatches(&validTargets, &validHatches);
			SortValidHatches(&validHatches);
			ChooseGoalHatch(&validHatches, &goal);

//			std::printf("C %d, B %d, T %d, P %d, x %d, y %d, w %d, h %d, d %5.1f, a %5.1f\n",
//				contours->size(), boundingRects.size(), validTargets.size(), validHatches.size(),
//				goal.r.x, goal.r.y, goal.r.width, goal.r.height, goal.dist, goal.angle);
		}

		frc::SmartDashboard::PutNumber("VisionThread", frc::SmartDashboard::GetNumber("VisionThread", 0) + 1);
		std::this_thread::sleep_for(std::chrono::milliseconds(65));

		// Draw the boundingRects on the frame bring processed -- white
		ApplyGridToFrame(inFrame, m_res /*, goal.dist, goal.angle*/);
		ApplyRectsToFrame(inFrame, &validTargets);
		ApplyHatchesToFrame(inFrame, &validHatches);
		ApplyGoalToFrame(inFrame, goal);
		outStream.PutFrame(inFrame);
	}
}

void VisionLoop::InitializeSmartdashboard(void) {

	// table = NetworkTable::GetTable("GRIP/myContoursReport");
	frc::SmartDashboard::PutBoolean(CAM_FOUNDTARGET, false);
	frc::SmartDashboard::PutNumber(CAM_TURNANGLE, 0.0);
	frc::SmartDashboard::PutNumber(CAM_DISTANCE, 0.0);

	// Initialize dashboard settings for camera
	frc::SmartDashboard::PutNumber(CAM_BRIGHTNESS, CAM_BRIGHTNESS_D);
	frc::SmartDashboard::PutNumber(CAM_EXPOSURE, CAM_EXPOSURE_D);

	// Initialize dashboard settings for pipeline
	frc::SmartDashboard::PutNumber(CAM_HUESTART, CAM_HUESTART_D);
	frc::SmartDashboard::PutNumber(CAM_HUEEND, CAM_HUEEND_D);
	frc::SmartDashboard::PutNumber(CAM_SATSTART, CAM_SATSTART_D);
	frc::SmartDashboard::PutNumber(CAM_SATEND, CAM_SATEND_D);
	frc::SmartDashboard::PutNumber(CAM_LUMSTART, CAM_LUMSTART_D);
	frc::SmartDashboard::PutNumber(CAM_LUMEND, CAM_LUMEND_D);
}

void VisionLoop::SetCamConfig(cs::UsbCamera cam) {

	static	pipeConfig visionPipe = VISIONPIPE_UNINIT;
	int	fps = 8; 							// Camera Frames Per Second
											// MS LifeCAM does not go below 8 fps
	int brightness = 0;						// Camera Brightness setting (0..100)
	int exposure = 0;						// Camera Exposure setting (0..100)

	if (s_visionPipe != visionPipe) {
		switch (s_visionPipe) {
		case VISIONPIPE_GEAR:
			ConfigureCamera(cam, m_res.width, m_res.height, fps, brightness, exposure);
			break;
		case VISIONPIPE_SHOOTER:
			ConfigureCamera(cam, m_res.width, m_res.height, fps, 50, 50);
			break;
		case VISIONPIPE_OFF:
		default:
			ConfigureCamera(cam, m_res.width, m_res.height, fps, 50, 50);
			break;
		}

		s_visionPipe = visionPipe;
	}
}

void VisionLoop::ConfigureCamera(cs::UsbCamera cam, int resWidth, int resHeight, int fps, int bright, int expos) {

	std::printf("2135: Configure camera - %d x %d, %d fps, %d bright, %d expos\n",
		resWidth, resHeight, fps, bright, expos);

	if (!cam.SetResolution(resWidth, resHeight))
		std::printf("2135: Cam resolution not set - %d\n", cam.GetLastStatus());
	if (!cam.SetFPS(fps))
		std::printf("2135: Cam FPS not set - %d\n", cam.GetLastStatus());
	cam.SetBrightness(bright);
	if (cam.GetLastStatus() != 0)
		std::printf("2135: Cam Brightness not set - %d\n", cam.GetLastStatus());
	cam.SetExposureManual(expos);
	if (cam.GetLastStatus() != 0)
		std::printf("2135: Cam Exposure not set - %d\n", cam.GetLastStatus());
}

bool VisionLoop::DetermineSlant(cv::RotatedRect *rotRect){
	cv::Point2f vert[4];
	bool bSlantRight(false);
	if (rotRect != NULL) {
		rotRect->points(vert);

		// printf("2135: ");
		// for (int i = 0; i < 4; i++) {
		// 	printf("vert[%d]=(%3f,%3f) ", i, (float)vert[i].x, (float)vert[i].y);
		// }
		// printf(" \n");

		float currLowestY = 500.0;
		float currGreatestY = 0.0;

		cv::Point2f lowestY;
		cv::Point2f greatestY;

		for (int i=0; i < 4; i++) {
			if (vert[i].y < currLowestY) {
				currLowestY = vert[i].y;
				lowestY = vert[i];
			}
			if (vert[i].y > currGreatestY) {
				currGreatestY = vert[i].y;
				greatestY = vert[i];
			}
		}

		if (lowestY.x < greatestY.x) bSlantRight = true;
	}
	return bSlantRight;
}

void VisionLoop::ConvertContoursToBoundingRects(std::vector<std::vector<cv::Point>> *contours, std::vector<tData> *rawData) {

	rawData->clear();

	// If contours are available, loop through up to 8 of them and create a vector of bounding rects
	if (!contours->empty()) {
		for (uint32_t i = 0; i < contours->size() && i < 8; i++) {
			tData rawt;
			rawt.r = cv::boundingRect(contours->at(i));
			cv::RotatedRect rotRect = cv::minAreaRect(contours->at(i));
			rawt.bSlantRight = DetermineSlant(&rotRect);
			rawData->push_back(rawt);
		}
	}
}

void VisionLoop::ConvertBoundingRectsToValidTargets(std::vector<tData> *rawData, std::vector<tData> *targets) {
	double	score;
	tData t;

	targets->clear();

	// If boundingRects are available, loop through them and create a vector of valid targets
	if (!rawData->empty()) {
		for (uint32_t i = 0; i < rawData->size(); i++) {
			cv::Rect r = rawData->at(i).r;

			// Translate width and height to floating point and calculate normalized score 0..100
			score = 100 * ((double)r.width / (double)r.height)
					* (m_targSize.height / m_targSize.width);

			// If the bounding rect score is close to 100, save it in the hold list
			if ( (score > 50) && (score < 200) ) {
				t.r = r;
				t.score = score;
				t.dist = CalcInchesToTarget(m_targSize.width , r);
				t.angle = CalcCenteringAngle(m_targSize.width, r, t.dist);
				t.bSlantRight = rawData->at(i).bSlantRight;
				targets->push_back(t);
				//std::printf("2135: Found valid target. bSlantRight = %d\n", t.bSlantRight);
			}
			PrintTargetData('T', i, t);
		}
	}
}

void VisionLoop::ConvertValidTargetsToValidHatches(std::vector<tData> *targets, std::vector<tData> *hatches) {
	double 	score;
	tData	h;

	hatches->clear();

	// If any validTargets are available, loop through them and create a vector of valid hatches
	if (targets->size() >= 2) {
		for (uint32_t i = 0; i < targets->size() - 1; i++) {
			cv::Rect targA = targets->at(i).r;

			for (uint32_t j = i+1; j < targets->size(); j++) {
				cv::Rect targB = targets->at(j).r;

				// Determine whether A or B is the leftmost target.
				tData leftMost = targets->at(i);
				tData rightMost = targets->at(j);

				if (targA.tl().x > targB.tl().x) {
					leftMost = targets->at(j);
					rightMost = targets->at(i);
				}

				// Check if left target is slanted right and right target is slanted left
				if (!leftMost.bSlantRight || rightMost.bSlantRight) {
					continue;
				}

				// Build a virtual contour around RectA and RectB (use top left/bottom right)
				std::vector<cv::Point> hatchPoints;
				hatchPoints.push_back(targA.tl());
				hatchPoints.push_back(targA.br());
				hatchPoints.push_back(targB.tl());
				hatchPoints.push_back(targB.br());
				cv::Rect hatchRect = cv::boundingRect(hatchPoints);

				// Translate width and height to floating point and calculate normalized score 0..100
				score = 100 * (((double)hatchRect.width / (double)hatchRect.height)
						* (m_hatchSize.height / m_hatchSize.width));

				// If the bounding rect score is close to 100, save it in the hold list
				if ((score > 50) && (score < 175)) {
					// Finding the distance from the camera to the hatch - group rect (in)
					h.r = hatchRect;
					h.score = score;
					h.dist = CalcInchesToTarget(m_hatchSize.width, hatchRect);
					h.angle = CalcCenteringAngle(m_hatchSize.width, hatchRect, h.dist);
					hatches->push_back(h);
					//std::printf("2135: Found a valid hatch. Score: %f\n", score); //For testing-
					//std::printf("Valid Hatch Pt 2: Distance: %f | Angle: %f\n", h.dist, h.angle); //For testing-

				}
			}
			PrintTargetData('H', i, h);
		}
	}
}

void VisionLoop::SortValidHatches(std::vector<tData> *hatches) {

	int size = hatches->size();

	if (size < 2) return;

	int i;
	int j;
	tData key;

	for (i = 1; i < size; i++) {
		key = hatches->at(i);
		j = i-1;

		while ((j >= 0) && (hatches->at(j).r.tl().x > key.r.tl().x)) {
			hatches->at(j+1) = hatches->at(j);
			j = j-1;
		}
		hatches->at(j+1) = key;
	}

	for (uint i=0; i<hatches->size(); i++) {
		std::printf("2135: Hatch %d: Top Left X: %d\n", i, hatches->at(i).r.tl().x);
	}
}

void VisionLoop::PrintTargetData(char name, int idx, tData t) {
	// std::printf("-%c %d: x %d, y %d, w %d, h %d, s %5.1f, d %5.1f, a %5.1f\n", name, idx,
	// 	t.r.x, t.r.y, t.r.width, t.r.height, t.score, t.dist, t.angle);
}

void VisionLoop::ApplyGridToFrame(cv::Mat frame, pixelRect res/*, double dist, double angle*/) {
	cv::Point	pt1, pt2;
	// char	str[32];

	pt1.x = 0;
	pt2.x = res.width;
	pt1.y = pt2.y = res.height / 2;
	cv::line(frame, pt1, pt2, cv::Scalar(255, 255, 255), 1, cv::LineTypes::LINE_4, 0);

	pt1.y = 0;
	pt2.y = res.height;
	pt1.x = pt2.x = res.width / 2;
	cv::line(frame, pt1, pt2, cv::Scalar(255, 255, 255), 1, cv::LineTypes::LINE_4, 0);

	// std::sprintf(str, "%5.1f in", dist);
	// pt1.x = 5;
	// pt1.y = res.height - 5;
	// cv::putText(frame, str, pt1, cv::FONT_HERSHEY_DUPLEX, 1.0, cv::Scalar(255, 255, 255),
	// 	1, cv::LineTypes::LINE_8, false);

	// std::sprintf(str, "%5.1f deg", angle);
	// pt1.x = res.width/2 - 10;
	// pt1.y = res.height - 5;
	// cv::putText(frame, str, pt1, cv::FONT_HERSHEY_DUPLEX, 1.0, cv::Scalar(255, 255, 255),
	// 	1, cv::LineTypes::LINE_8, false);
}

void VisionLoop::ApplyRectsToFrame(cv::Mat frame, std::vector<tData> *targets) {
	for (uint32_t i = 0; i < targets->size(); i++) {
		cv::Rect& tRect = targets->at(i).r;
		cv::rectangle(frame, tRect, cv::Scalar(68, 68, 255), 2, cv::LineTypes::LINE_8);
	}
}

void VisionLoop::ApplyHatchesToFrame(cv::Mat frame, std::vector<tData> *hatches) {

for (uint32_t i = 0; i < hatches->size(); i++) {
		tData& tHatch = hatches->at(i);

		cv::Point	pt1, pt2;

		cv::rectangle(frame, tHatch.r, cv::Scalar(68, 255, 68), 2, cv::LineTypes::LINE_8);

		pt1.x = tHatch.r.x + tHatch.r.width/2 - 5;
		pt2.x = pt1.x + 10;
		pt1.y = pt2.y = tHatch.r.y + tHatch.r.height/2;
		cv::line(frame, pt1, pt2, cv::Scalar(68, 255, 68), 1, cv::LineTypes::LINE_4, 0);

		pt1.y = tHatch.r.y + tHatch.r.height/2 - 5;
		pt2.y = pt1.y + 10;
		pt1.x = pt2.x = tHatch.r.x + tHatch.r.width/2;
		cv::line(frame, pt1, pt2, cv::Scalar(68, 255, 68), 1, cv::LineTypes::LINE_4, 0);
	}
}

void VisionLoop::ApplyGoalToFrame(cv::Mat frame, tData goal) {
	cv::Point	pt1, pt2;

	cv::rectangle(frame, goal.r, cv::Scalar(255,105,180), 2, cv::LineTypes::LINE_8);

	pt1.x = goal.r.x + goal.r.width/2 - 5;
	pt2.x = pt1.x + 10;
	pt1.y = pt2.y = goal.r.y + goal.r.height/2;
	cv::line(frame, pt1, pt2, cv::Scalar(255,105,180), 1, cv::LineTypes::LINE_4, 0);

	pt1.y = goal.r.y + goal.r.height/2 - 5;
	pt2.y = pt1.y + 10;
	pt1.x = pt2.x = goal.r.x + goal.r.width/2;
	cv::line(frame, pt1, pt2, cv::Scalar(255,105,180), 1, cv::LineTypes::LINE_4, 0);
}

double VisionLoop::CalcInchesToTarget(double targetWidthInches, cv::Rect rect) {
	// Calculate the distance to the target given using the camera Field of View (FOV)
	//	Distance to target for a Field of View of 50 degrees filling the screen with a 2.0" target
	//		D = (2.0"/2) / tan(50deg / 2) = 2.144"
	//	Calculate Focal length using D = 2.144"
	//	Focal_length = Width_pixels x Distance / Target_width
	//		F = (P x D) / W = 320px x 2.144" / 2.0" = 343.2
	//		D = (F x W) / P = (343.2 x 2.0") / P
	//		D = 320px x (1 / tan(50/2)) / Measured pixels

	return (343.2 * targetWidthInches) / rect.width;
}

double VisionLoop::CalcCenteringAngle(double targetWidthInches, cv::Rect rect, double inchesToTarget) {
	// Frame coordinate system goes from X (0 -> 320) and Y (0 -> 240)
	// Find frame X coordinate of rect center (rect is the vision target)
	double rectCenterX = (double)rect.x + (double)(rect.width)/2.0;

	// Calculate the number of pixels needed to center the rect in the frame
	double pixelsToCenter = rectCenterX - m_res.width/2.0;

	// Convert from pixels into inches to center the rect in the frame
	double inchesToCenter = targetWidthInches * pixelsToCenter / (double)(rect.width);

	// Convert from inches to radians to center the rect in the frame thru inverse tangent
	double radiansToCenter = atan(inchesToCenter / inchesToTarget);

	// Convert from radians to degrees to center the rect in the frame
	return radiansToCenter * 180.0 / M_PI;
}

void VisionLoop::ChooseGoalHatch(std::vector<tData> *hatches, tData *goal) {
	if (!hatches->empty()) {
		goal = &(hatches->front());									// Get first hatch which should be the leftmost hatch
		frc::SmartDashboard::PutBoolean(CAM_FOUNDTARGET, true);
		frc::SmartDashboard::PutNumber(CAM_TURNANGLE, goal->angle);
		frc::SmartDashboard::PutNumber(CAM_DISTANCE, goal->dist);
	}

	else {
		goal = nullptr;
		frc::SmartDashboard::PutBoolean(CAM_FOUNDTARGET, false);
		frc::SmartDashboard::PutNumber(CAM_TURNANGLE, 0.0);
		frc::SmartDashboard::PutNumber(CAM_DISTANCE, 0.0);
	}
}