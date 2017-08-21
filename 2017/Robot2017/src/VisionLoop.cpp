/*
 * VisionThread.cpp
 *
 *  Created on: Aug 6, 2017
 *      Author: PHS_User
 */

#include <src/VisionLoop.h>

VisionLoop::VisionLoop() {
	printf("2135: VisionLoop Constructor\n");
}

VisionLoop::~VisionLoop() {
	// TODO Auto-generated destructor stub
}

void VisionLoop::Run() {

	printf("2135: VisionLoop Run\n");

	m_res.width = 320;							// Camera Resolution setting in pixels
	m_res.height = 240;
	int	fps = 8; 								// Camera Frames Per Second
												// MS LifeCAM does not go below 8 fps
	int brightness = 0;						// Camera Brightness setting (0..100)
	int exposure = 0;							// Camera Exposure setting (0..100)
	m_targSize.width = 2.0;						// 2017 Vision target dimensions
	m_targSize.height = 5.0;
	m_pegSize.width = 10.25;					// 2017 Peg (two targets) dimensions
	m_pegSize.height = 5.0;

	// CameraServer structures for processing vision frames
	cs::CvSink inStream;
	cs::CvSource outStream;
	std::unique_ptr<grip::GripContoursPipeline> gripPipe;

	// OpenCV structures for processing vision frames
	cv::Mat inFrame;
	cv::Mat gripFrame;

	// Image processing structures for identifying targets
	std::vector<std::vector<cv::Point>> *contours;
	std::vector<cv::Rect> boundingRects;
	std::vector<tData> validTargets;
	std::vector<tData> validPegs;
	tData goal;

	// Get initial settings from SmartDashboard
	InitializeSmartdashboard();

	// Our camera input source - start it up and configure settings
	cs::UsbCamera cam = CameraServer::GetInstance()->StartAutomaticCapture();
	ConfigureCamera(cam, m_res.width, m_res.height, fps, brightness, exposure);

	// Start our GRIP-generated vision processing pipeline
	gripPipe.reset(new grip::GripContoursPipeline());

	// Set our input/output stream - available to the dashboard (same resolution as input)
	inStream = CameraServer::GetInstance()->GetVideo();
	outStream = CameraServer::GetInstance()->PutVideo("Contours Video", m_res.width, m_res.height);

	// Main loop for our vision thread
	while (true) {
		int validFrame = inStream.GrabFrame(inFrame, 1000);

		if ((validFrame == 0) || (inFrame.empty())) {
		    std::string error = inStream.GetError();
		    DriverStation::ReportError(error);
		    printf("2135: Missed frame\n");
			std::this_thread::sleep_for(std::chrono::milliseconds(250));
		    continue;
		}
		else {
			// Run vision processing gripPipe generated from GRIP
			gripPipe->Process(inFrame);
			gripFrame = *(gripPipe->gethslThresholdOutput());
			contours = gripPipe->getfilterContoursOutput();

			ConvertContoursToBoundingRects(contours, &boundingRects);
			ConvertBoundingRectsToValidTargets(&boundingRects, &validTargets);
			ConvertValidTargetsToValidPegs(&validTargets, &validPegs);
			ChooseGoalPeg(&validPegs, &goal);

			printf("C %d, B %d, T %d, P %d, x %d, y %d, w %d, h %d, d %5.1f, a %5.1f\n",
				contours->size(), boundingRects.size(), validTargets.size(), validPegs.size(),
				goal.r.x, goal.r.y, goal.r.width, goal.r.height, goal.dist, goal.angle);

			SmartDashboard::PutNumber("VisionThread", SmartDashboard::GetNumber("VisionThread", 0) + 1);
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		// Draw the boundingRects on the frame bring processed -- white
		ApplyRectsToFrame(inFrame, boundingRects);
		outStream.PutFrame(inFrame);
	}
}

void VisionLoop::InitializeSmartdashboard(void) {

	// table = NetworkTable::GetTable("GRIP/myContoursReport");
	SmartDashboard::PutBoolean(CAM_FOUNDTARGET, false);
	SmartDashboard::PutBoolean(CAM_GEARPIPEON, false);
	SmartDashboard::PutBoolean(CAM_SHOOTERPIPEON, false);

	SmartDashboard::PutNumber(CAM_TURNANGLE, 0.0);
	SmartDashboard::PutBoolean(CAM_FOUNDTARGET, true);

	// Initialize dashboard settings for camera
	SmartDashboard::PutNumber(CAM_BRIGHTNESS, CAM_BRIGHTNESS_D);
	SmartDashboard::PutNumber(CAM_EXPOSURE, CAM_EXPOSURE_D);

	// Initialize dashboard settings for pipeline
	SmartDashboard::PutNumber(CAM_HUESTART, CAM_HUESTART_D);
	SmartDashboard::PutNumber(CAM_HUEEND, CAM_HUEEND_D);
	SmartDashboard::PutNumber(CAM_SATSTART, CAM_SATSTART_D);
	SmartDashboard::PutNumber(CAM_SATEND, CAM_SATEND_D);
	SmartDashboard::PutNumber(CAM_LUMSTART, CAM_LUMSTART_D);
	SmartDashboard::PutNumber(CAM_LUMEND, CAM_LUMEND_D);
}

void VisionLoop::ConfigureCamera(cs::UsbCamera cam, int resWidth, int resHeight, int fps, int bright, int expos) {

	printf("2135: Configure camera - %d x %d, %d fps, %d bright, %d expos\n",
		resWidth, resHeight, fps, bright, expos);

	if (!cam.SetResolution(resWidth, resHeight))
		printf("2135: Cam resolution not set - %d\n", cam.GetLastStatus());
	if (!cam.SetFPS(fps))
		printf("2135: Cam FPS not set - %d\n", cam.GetLastStatus());
	cam.SetBrightness(bright);
	if (cam.GetLastStatus() != 0)
		printf("2135: Cam Brightness not set - %d\n", cam.GetLastStatus());
	cam.SetExposureManual(expos);
	if (cam.GetLastStatus() != 0)
		printf("2135: Cam Exposure not set - %d\n", cam.GetLastStatus());
}

void VisionLoop::ConvertContoursToBoundingRects(std::vector<std::vector<cv::Point>> *contours, std::vector<cv::Rect> *rects) {

	rects->clear();

	// If any contours are available, loop through them and create a vector of bounding rects
	if (contours->size() > 0) {
		for (uint32_t i = 0; i < contours->size() && i < 8; i++) {
			rects->push_back(cv::boundingRect((*contours)[i]));
		}
	}
}

void VisionLoop::ConvertBoundingRectsToValidTargets(std::vector<cv::Rect> *boundingRects, std::vector<tData> *targets) {
	double	score;
	tData t;

	targets->clear();

	// If any boundingRects are available, loop through them and create a vector of valid targets
	if (boundingRects->size() > 0) {
		for (uint32_t i = 0; i < boundingRects->size(); i++) {
			cv::Rect *r = boundingRects->data();

			// Translate width and height to floating point and calculate normalized score 0..100
			score = 100 * ((double)r[i].width / (double)r[i].height)
					* (m_targSize.height / m_targSize.width);

			// If the bounding rect score is close to 100, save it in the hold list
			if ( (score > 50) && (score < 200) ) {
				t.r = r[i];
				t.score = score;
				t.dist = CalcInchesToTarget(m_targSize.width , r[i]);
				t.angle = CalcCenteringAngle(m_targSize.width, r[i], t.dist);
				targets->push_back(t);
			}
		}
	}
}

void VisionLoop::ConvertValidTargetsToValidPegs(std::vector<tData> *targets, std::vector<tData> *pegs) {

	double 	score;
	std::vector<tData>::iterator it = targets->begin();
	tData	p;

	pegs->clear();

	// If any validTargets are available, loop through them and create a vector of valid pegs
	if (targets->size() >= 2) {
		for (uint32_t i = 0; i < targets->size() - 1; i++) {
			cv::Rect targA = targets->at(i).r;

			for (uint32_t j = i+1; j < targets->size(); j++) {
				cv::Rect targB = targets->at(j).r;

				// Build a virtual contour around RectA and RectB (use top left/bottom right)
				std::vector<cv::Point> pegPoints;
				pegPoints.push_back(targA.tl());
				pegPoints.push_back(targA.br());
				pegPoints.push_back(targB.tl());
				pegPoints.push_back(targB.br());
				cv::Rect pegRect = cv::boundingRect(pegPoints);

				// Translate width and height to floating point and calculate normalized score 0..100
				score = 100 * (((double)pegRect.width / (double)pegRect.height)
						* (m_pegSize.height / m_pegSize.width));

				// If the bounding rect score is close to 100, save it in the hold list
				if ((score > 50) && (score < 200)) {
					// Finding the distance from the camera to the peg - group rect (in)
					p.r = pegRect;
					p.score = score;
					p.dist = CalcInchesToTarget(m_pegSize.width, pegRect);
					p.angle = CalcCenteringAngle(m_pegSize.width, pegRect, p.dist);
					pegs->push_back(p);
//					printf("-P-> %2d, X %d, Y %d, W %d, H %d, score %3f, dist %f, angle %f\n",
//							i, pegRect.x, pegRect.y, pegRect.width, pegRect.height, p.score, p.dist, p.angle);
				}
			}
		}
	}
}

void VisionLoop::ChooseGoalPeg(std::vector<tData> *pegs, tData *goal) {

	std::memset(goal, 0, sizeof(tData));

	if (pegs->size()) {
		memcpy(goal, &pegs[0], sizeof(tData));
	}
}

void VisionLoop::ApplyRectsToFrame(cv::Mat frame, std::vector<cv::Rect> rects) {
	for (uint32_t i = 0; i < rects.size(); i++) {
		cv::rectangle(frame, rects[i], cv::Scalar(68, 68, 255), 2, cv::LineTypes::LINE_8);
	}
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
	// 	targetWidthInches * FOVpixels / (2 * RectWidthPixels * tan(FOVradians / 2.0)

	const double fovDegrees = 50.0;					// Using camera horizontoal FOV = 50 degrees
	double fovRadians = fovDegrees * M_PI / 180.0;	// Convert FOV degrees to radians

	// Use equivalent triangles and half the FOV angle in radians
//	return ((targetWidthInches / 2.0) * m_res.width * (1 / tan(fovRadians/2)) * rect.width);
	return ((targetWidthInches / 2.0) * m_res.width * (1 / tan(fovRadians/2)) * rect.width);
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

// Toggle mode for enabling/disabling the pipelines on the cameras for gear and shooter.

void VisionLoop::VisionGearPipeOn() {
	SmartDashboard::PutBoolean(CAM_GEARPIPEON, true);
}

void VisionLoop::VisionShooterPipeOn() {
	SmartDashboard::PutBoolean(CAM_SHOOTERPIPEON, true);
}

void VisionLoop::VisionAllPipesOff() {
	SmartDashboard::PutBoolean(CAM_GEARPIPEON, false);
	SmartDashboard::PutBoolean(CAM_SHOOTERPIPEON, false);
}
