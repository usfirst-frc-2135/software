// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Robot.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
std::shared_ptr<Chassis> Robot::chassis;
std::shared_ptr<Climber> Robot::climber;
std::shared_ptr<Intake> Robot::intake;
std::shared_ptr<Shooter> Robot::shooter;
std::shared_ptr<Delivery> Robot::delivery;
std::shared_ptr<Pneumatics> Robot::pneumatics;
std::unique_ptr<OI> Robot::oi;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION

void Robot::RobotInit() {
	RobotMap::init();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    chassis.reset(new Chassis());
    climber.reset(new Climber());
    intake.reset(new Intake());
    shooter.reset(new Shooter());
    delivery.reset(new Delivery());
    pneumatics.reset(new Pneumatics());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi.reset(new OI());

	// instantiate the command used for the autonomous period
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	autonomousCommand.reset(new AutonomousCommand());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS

	table = NetworkTable::GetTable("GRIP/myContoursReport");
}

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit(){

}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	Robot::chassis->ResetGyro();

	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Cancel();


}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();

	std::vector<double> arr = table->GetNumberArray("area", llvm::ArrayRef<double>());
	for (unsigned int i = 0; i < arr.size(); i++) {
//		printf("2135: %f\n", arr[i]);
	}

	SmartDashboard::PutNumber("Gyro Value", Robot::chassis->ReadGyro());
}

void Robot::TestPeriodic() {
	lw->Run();
}

//	Vision processing thread

Robot::Robot():visionThread(CameraVisionThread) {

}

// Vision processing thread

void Robot::CameraVisionThread(){
	// Declare vision thread variables

	// Our camera input source - start it up
	cs::UsbCamera camera = CameraServer::GetInstance()->StartAutomaticCapture();
//	camera.SetResolution(imgWidth, imgHeight);

	// Our vision processing pipeline
	grip::GripContoursPipeline cameraPipeline;

	// Our output stream - available to the dashboard (uses same resolution as input)
	cs::CvSink inputStream = CameraServer::GetInstance()->GetVideo();
	cs::CvSource outputStream = CameraServer::GetInstance()->PutVideo("Contours Video", imgWidth, imgHeight);

	// OpenCV structures for processing vision frames
	cv::Mat inputFrame;
	cv::Mat processFrame;

	// Initialize dashboard settings for camera
	SmartDashboard::PutNumber("Camera Brightness %", 0);
	SmartDashboard::PutNumber("Camera Exposure %", 0);

	// Initialize dashboard settings for pipeline
	SmartDashboard::PutNumber("Hue Start", 0.0);
	SmartDashboard::PutNumber("Hue End", 102.0);
	SmartDashboard::PutNumber("Saturation Start", 202.0);
	SmartDashboard::PutNumber("Saturation End", 255.0);
	SmartDashboard::PutNumber("Luminance Start", 24.0);
	SmartDashboard::PutNumber("Luminance End", 255.0);

	// Main loop for our vision thread
	while (true) {
		// DEBUG ONLY: Wait one second before starting each processing loop
		std::this_thread::sleep_for(std::chrono::seconds(1));

		// Get the current brightness from the dashboard
		//	TODO: getting values from the dashboard is reinputFrame intensive--only do it occasionally
		//		Maybe only do it when we do TelopInit or AutonInit
		int camBrightness = SmartDashboard::GetNumber("Camera Brightness %", 0);
		camera.SetBrightness(camBrightness);

		// Get the current exposure from the dashboard
		//	TODO: only do this occasionally - resource intensive
		int camExposure = SmartDashboard::GetNumber("Camera Exposure %", 0);
		camera.SetExposureManual(camExposure);

		// Get a frame from the camera input stream
		inputStream.GrabFrame(inputFrame);
		// Run vision processing pipeline generated from GRIP
		cameraPipeline.Process(inputFrame);
		// Get a reference to the pipeline output frame
		processFrame = *(cameraPipeline.gethslThresholdOutput());

		// Get a reference to the pipeline output contours
		std::vector<std::vector<cv::Point> >* filterContours = cameraPipeline.getfilterContoursOutput();

		// Declare a temporary holding list for validated rects
		std::vector<cv::Rect> validRectList;

		// Match flag initilaization
		bool foundMatch = false;

		// Loop through the contours list and add bounding rects to the video stream
		for (unsigned int i = 0; i < filterContours->size(); i++) {
			// Declare an array reference to the filter contours from the pipeline
			std::vector<cv::Point>& contour = (*filterContours)[i];

			// Calculate the bounding rectangle for the contour
			cv::Rect rect = cv::boundingRect(contour);

			// Draw the rectangle formed by boundingRect on the frame bring processed -- white
			cv::rectangle(processFrame, rect, cv::Scalar(255, 255, 255));

			// Translate width and height to floating point and calculate normalized aspect ratio
			float rectWidth = (float)rect.width;
			float rectHeight = (float)rect.height;
			float rectRatio = (rectWidth / rectHeight) * 5.0/2.0;

			// If the rect is the correct rectangle target shape, save it in the hold list
			if ((rectRatio > 0.8) && (rectRatio < 1.2)) {
				printf("2135: Boundary Rect in Hold List: %d\n", validRectList.size());
				validRectList.push_back(rect);
			}
		}

		// Print the number of valid rects stored in list
		printf("2135: Boundary rects in list: %d\n", validRectList.size());

		// Need two contours in the hold list in order to make a group
		if (validRectList.size() > 1) {
			// Loop through validated rect list
			for (unsigned int itr = 0; itr < validRectList.size(); itr++) {
				// Initialize first rect before comparing the two
				cv::Rect& rectA = validRectList[itr];

				// Loop through remaining valid rects to validate the pair
				for (unsigned int itr2 = (itr + 1); itr < validRectList.size(); itr2++) {
					// Initialize second rect
					cv::Rect&  rectB = validRectList[itr2];

					// Don't compare rect against itself--skip it
					if (rectA == rectB) {
						continue;
					}

					// Set up the points for the bounding box around RectA and RectB
					std::vector<cv::Point> groupPoints;
					cv::Point groupPoint1(rectA.x, rectA.y);
					cv::Point groupPoint2(rectA.x, rectA.y + rectA.height);
					cv::Point groupPoint3(rectA.x + rectA.width, rectA.y + rectA.height);
					cv::Point groupPoint4(rectA.x + rectA.width + rectA.y);
					cv::Point groupPoint5(rectB.x, rectB.y);
					cv::Point groupPoint6(rectB.x, rectB.y + rectB.height);
					cv::Point groupPoint7(rectB.x + rectB.width, rectB.y + rectB.height);
					cv::Point groupPoint8(rectB.x + rectB.width + rectB.y);

					// Set up a contour withthe list of points to get a bounding rect surrounding both
					groupPoints.push_back(groupPoint1);
					groupPoints.push_back(groupPoint2);
					groupPoints.push_back(groupPoint3);
					groupPoints.push_back(groupPoint4);
					groupPoints.push_back(groupPoint5);
					groupPoints.push_back(groupPoint6);
					groupPoints.push_back(groupPoint7);
					groupPoints.push_back(groupPoint8);

					// Get the boundingRect around both valid individual targets
					cv::Rect groupRect = cv::boundingRect(groupPoints);

					// Checking the groupRect height:width ratio to verify bounding Rect
					float groupRectWidth = (float)groupRect.width;
					float groupRectHeight = (float)groupRect.height;
					float groupRectRatio = ((groupRectWidth / groupRectHeight) * (5.0 / 10.25));

					// Validate the grouped targets as being of the correct aspect ratio
					if ((groupRectRatio > 0.8) && (groupRectRatio < 1.2)) {
						// Found a possible match
						printf("!!! ---> 2135: Found a group ratio: %3f\n", groupRectRatio);
						// Add the valid group rect to the frame being processed
						cv::rectangle(processFrame, groupRect, cv::Scalar(0, 0, 255));
						foundMatch = true;
						// Find the center point of groupRect to get peg location
						float centerX = (float)(groupRect.x) + (float)(groupRect.width)/2.0;
						float centerY = (float)(groupRect.y) + (float)(groupRect.height)/2.0;
						printf("+++ 2135: Group rect center point (%d, %d)\n", (int)centerX, (int)centerY);
						// Find the height, width, x, y of the groupRect
						printf("---> 2135: Group rect height: %d, width: %d, x: %d, y: %d\n", groupRect.height, groupRect.width, groupRect.x, groupRect.y);
						break;
					}
					else continue;
				} // End itr2

				if (foundMatch) {
					break;
				}
			} // End itr1

	//		if (foundMatch) {
				// Display the final processed frame
				printf("2135: Display processed frame\n");
				outputStream.PutFrame(processFrame);
	//		}
	//		else printf("2135: No peg target match found\n");

	//		SmartDashboard::PutNumberArray("Contour x", table->GetNumberArray("centerX", llvm::ArrayRef<double>()));
	//		SmartDashboard::PutNumberArray("Contour y", table->GetNumberArray("centerY", llvm::ArrayRef<double>()));
	//		SmartDashboard::PutNumberArray("Contour area", table->GetNumberArray("area", llvm::ArrayRef<double>()));
		}
	}
}

START_ROBOT_CLASS(Robot);

