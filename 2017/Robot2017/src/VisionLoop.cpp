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

	res.width = 320;							// Camera Resolution setting in pixels
	res.height = 240;
	int	fps = 8; 								// Camera Frames Per Second
												// MS LifeCAM does not go below 8 fps
	int brightness = 50;						// Camera Brightness setting (0..100)
	int exposure = 50;							// Camera Exposure setting (0..100)
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
	std::vector<cv::Rect> validTargets;
	std::vector<cv::Rect> validPegs;

	// Get initial settings from SmartDashboard
	InitializeSmartdashboard();

	// Our camera input source - start it up and configure settings
	cs::UsbCamera cam = CameraServer::GetInstance()->StartAutomaticCapture();
	ConfigureCamera(cam, res.width, res.height, fps, brightness, exposure);

	// Start our GRIP-generated vision processing pipeline
	gripPipe.reset(new grip::GripContoursPipeline());

	// Set our input/output stream - available to the dashboard (same resolution as input)
	inStream = CameraServer::GetInstance()->GetVideo();
	outStream = CameraServer::GetInstance()->PutVideo("Contours Video", res.width, res.height);

	// Main loop for our vision thread
	while (true) {
		int validFrame = inStream.GrabFrame(inFrame, 1000);
		outStream.PutFrame(inFrame);

		if (validFrame == 0) {
		    std::string error = inStream.GetError();
		    DriverStation::ReportError(error);
		    printf("2135: Missed frame\n");
			std::this_thread::sleep_for(std::chrono::milliseconds(250));
		    continue;
		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			printf("2135: Tick\n");
			continue;

			SmartDashboard::PutString("VisionThread", "Testing");

			// Run vision processing gripPipe generated from GRIP
			gripPipe->Process(inFrame);
			gripFrame = *(gripPipe->gethslThresholdOutput());
			contours = gripPipe->getfilterContoursOutput();

			ConvertContoursToBoundingRects(contours, &boundingRects);
			ConvertBoundingRectsToValidTargets(&boundingRects, &validTargets);

			// See if we have 1 or more targets to work on
			if (validTargets.size() > 0) {
				double distance;
				double angle;
				if (validTargets.size() == 1) {
					// Exactly one valid target - not enough info except to maybe drive
					distance = CalcInchesToTarget(m_targSize.width , validTargets[0]);
					angle = CalcCenteringAngle(m_targSize.width, validTargets[0], distance);
				}
				else {
					// Must be at least 2 valid targets
					ConvertValidTargetsToValidPegs(&validTargets, &validPegs);
					distance = CalcInchesToTarget(m_pegSize.width , validPegs[0]);
					angle = CalcCenteringAngle(m_pegSize.width, validPegs[0], distance);
				}
				printf("--> TARGETS: %d  Distance: %3f Angle: %3f\n", validTargets.size(), distance, angle);
			}
			printf("--> -------------------------------- <--\n");
		}

#if 0
		// Draw the boundingRects on the frame bring processed -- white
		gripFrame = *(gripPipe->gethslThresholdOutput());
		ApplyRectsToFrame(gripFrame, boundingRects);
		outStream.PutFrame(gripFrame);
#else
		outStream.PutFrame(inFrame);
#endif
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

	if (!cam.SetResolution(resWidth, resHeight))
		;
		printf("2135: Cam resolution not set - %d\n", cam.GetLastStatus());
	if (!cam.SetFPS(fps))
		;
		printf("2135: Cam FPS not set - %d\n", cam.GetLastStatus());
	cam.SetBrightness(bright);
	printf("2135: Cam Brightness status - %d\n", cam.GetLastStatus());
	cam.SetExposureManual(expos);
	printf("2135: Cam Exposure status - %d\n", cam.GetLastStatus());
}

void VisionLoop::ConvertContoursToBoundingRects(std::vector<std::vector<cv::Point>> *contours, std::vector<cv::Rect> *rects) {

	printf("--> Found %d contours\n", contours->size());

	rects->clear();

	// Loop through the contours list (max 8) and create a vector of bounding rects
	for (uint32_t i = 0; i < contours->size() && i < 8; i++) {

		// Calculate the bounding rectangle for the contour
		rects->push_back(cv::boundingRect(contours[i]));
	}

	printf("-C-> Created %d bounding rects\n", rects->size());
}

double VisionLoop::ConvertBoundingRectsToValidTargets(std::vector<cv::Rect> *boundingRects, std::vector<cv::Rect> *targets) {
	double	score;

	targets->clear();

	// Loop through bounding rects and create a vector of valid targets
	for (uint32_t i = 0; i < boundingRects->size(); i++)
	{
		cv::Rect *r = boundingRects->data();

		// Translate width and height to floating point and calculate normalized score 0..100
		score = 100 * ((double)r[i].width / (double)r[i].height) * (m_targSize.height / m_targSize.width);

		// If the bounding rect score is close to 100, save it in the hold list
		if ( (score > 50) && (score < 200) ) {
			printf("-T-> %2d, X %3d, Y %3d, W %3d, H %3d, score %3f\n", i, r->x, r->y, r[i].width, r[i].height, score);
			targets->push_back(r[i]);
		}
	}

	printf("-T-> Created %d valid targets\n", targets->size());

	return score;
}

double VisionLoop::ConvertValidTargetsToValidPegs(std::vector<cv::Rect> *targets, std::vector<cv::Rect> *pegs) {

	double score;

	pegs->clear();

	// Must be at least two rects available to get here, initialize first
	cv::Rect *rectA = targets->data();

	// Loop through remaining valid target list to find a valid peg
	for (uint32_t i = 0; i < targets->size() - 1; i++) {
		cv::Rect *rectB = rectA + i;

		// Build a virtual contour around RectA and RectB (use top left/bottom right)
		std::vector<cv::Point> pegPoints;
		pegPoints.push_back(rectA->tl());
		pegPoints.push_back(rectA->br());
		pegPoints.push_back(rectB->tl());
		pegPoints.push_back(rectB->br());
		cv::Rect pegRect = cv::boundingRect(pegPoints);

		// Translate width and height to floating point and calculate normalized score 0..100
		score = 100 * (((double)pegRect.width / (double)pegRect.height) * (m_pegSize.height / m_pegSize.width));

		// If the bounding rect score is close to 100, save it in the hold list
		if ((score > 50) && (score < 200)) {
			// Finding the distance from the camera to the peg - group rect (in)
			double distance = CalcInchesToTarget(m_pegSize.width, pegRect);
			double angle = CalcCenteringAngle(m_pegSize.width, pegRect, distance);
			printf("-P-> %2d, X %d, Y %d, W %d, H %d, score %3f, dist %f, angle %f\n",
					i, pegRect.x, pegRect.y, pegRect.width, pegRect.height, score, distance, angle);
			break;
		}
	}

	return score;
}

void VisionLoop::ApplyRectsToFrame(cv::Mat frame, std::vector<cv::Rect> rects) {
	for (uint32_t i = 0; i < rects.size(); i++) {
		cv::rectangle(frame, rects[i], cv::Scalar(255, 255, 255));
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
	return ((targetWidthInches / 2.0) * res.width * (1 / tan(fovRadians/2)) * rect.width);
}

double VisionLoop::CalcCenteringAngle(double targetWidthInches, cv::Rect rect, double inchesToTarget) {
	// Frame coordinate system goes from X (0 -> 320) and Y (0 -> 240)
	// Find frame X coordinate of rect center (rect is the vision target)
	double rectCenterX = (double)rect.x + (double)(rect.width)/2.0;

	// Calculate the number of pixels needed to center the rect in the frame
	double pixelsToCenter = rectCenterX - res.width/2.0;

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
