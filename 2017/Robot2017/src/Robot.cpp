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
#include "Commands/AutonDefault.h"
#include "Commands/AutonPos123Move.h"
#include "Commands/AutonPos1DeliverGear.h"
#include "Commands/AutonPos2DeliverGear.h"
#include "Commands/AutonPos3DeliverGear.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
std::shared_ptr<Chassis> Robot::chassis;
std::shared_ptr<Intake> Robot::intake;
std::shared_ptr<Agitator> Robot::agitator;
std::shared_ptr<Shooter> Robot::shooter;
std::shared_ptr<Delivery> Robot::delivery;
std::shared_ptr<Climber> Robot::climber;
std::shared_ptr<Pneumatics> Robot::pneumatics;
std::shared_ptr<Power> Robot::power;
std::unique_ptr<OI> Robot::oi;
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION

void Robot::RobotInit() {
	RobotMap::init();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    chassis.reset(new Chassis());
    intake.reset(new Intake());
    agitator.reset(new Agitator());
    shooter.reset(new Shooter());
    delivery.reset(new Delivery());
    climber.reset(new Climber());
    pneumatics.reset(new Pneumatics());
    power.reset(new Power());
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi.reset(new OI());

	// instantiate the command used for the autonomous period
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	autonomousCommand.reset(new AutonDefault());
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS

	table = NetworkTable::GetTable("GRIP/myContoursReport");
	SmartDashboard::PutBoolean(CAM_FOUNDTARGET, false);

	m_faultsCleared = false;
	m_dashboardUpdate = 0;

	prefs = frc::Preferences::GetInstance();

	Robot::VisionAllPipesOff();
  }

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit(){
	m_faultsCleared = false;

	chooser.AddDefault("Auton Default", new AutonDefault());
	chooser.AddObject("Pos 123 Move", new AutonPos123Move());
	chooser.AddObject("Pos 1 Gear", new AutonPos1DeliverGear());
	chooser.AddObject("Pos 2 Gear", new AutonPos2DeliverGear());
	chooser.AddObject("Pos 3 Gear", new AutonPos3DeliverGear());
	frc::SmartDashboard::PutData("Auto Modes", &chooser);
}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();

	// If RoboRIO User button is pressed, dump faults
	if (GetUserButton() && !m_faultsCleared) {
		m_faultsCleared = true;
		HandleFaults();
	}

	//	Print dashboard values only occassionally to reduce resource requirements
	if (m_dashboardUpdate++ > smartdashboardUpdateDisabled)
	{
		m_dashboardUpdate = 0;
		Robot::chassis->UpdateSmartDashboardValues();
	}
}

void Robot::AutonomousInit() {
	prefs = frc::Preferences::GetInstance();

	// Initialize SmartDashboard preferences
	chassis->Initialize(prefs);
	fflush(stdout);
	agitator->Initialize(prefs);
	fflush(stdout);
	climber->Initialize(prefs);
	fflush(stdout);
	delivery->Initialize(prefs);
	fflush(stdout);
	intake->Initialize(prefs);
	fflush(stdout);
	pneumatics->Initialize(prefs);
	fflush(stdout);
	shooter->Initialize(prefs);
	fflush(stdout);

	autonomousCommand.reset(chooser.GetSelected());
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();

	//	Print dashboard values only occasionally to reduce resource requirements
	if (m_dashboardUpdate++ > smartdashboardUpdateAutonomous)
	{
		m_dashboardUpdate = 0;
		Robot::chassis->UpdateSmartDashboardValues();
	}
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Cancel();

	prefs = frc::Preferences::GetInstance();

	// Initialize SmartDashboard and Subsystems
	chassis->Initialize(prefs);
	fflush(stdout);
	agitator->Initialize(prefs);
	fflush(stdout);
	climber->Initialize(prefs);
	fflush(stdout);
	delivery->Initialize(prefs);
	fflush(stdout);
	intake->Initialize(prefs);
	fflush(stdout);
	pneumatics->Initialize(prefs);
	fflush(stdout);
	shooter->Initialize(prefs);
	fflush(stdout);
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();

	//	Print dashboard values only occasionally to reduce resource requirements
	if (m_dashboardUpdate++ > smartdashboardUpdateTeleop)
	{
		m_dashboardUpdate = 0;
		Robot::chassis->UpdateSmartDashboardValues();
	}

#if 1
	// Read contour array from SmartDashboard and print it
	std::vector<double> arr;

	arr = table->GetNumberArray("area", llvm::ArrayRef<double>());
	for (unsigned int i = 0; i < arr.size(); i++) {
		printf("2135: %f\n", arr[i]);
	}
#endif

#if 1
	// For 1 each of 10 passes through TeleopPeriodic, check and process angle
	static int counter = 0;

	if (counter <= 10) {
		counter++;
	}
	else {
		counter = 0;
		if (SmartDashboard::GetBoolean(CAM_FOUNDTARGET, false) == true) {
//			double temp;
//			double angleToAdjust;
//			bool turnRight;

			// TODO: This should be cleaned up (while testing it). The angle
			//	to adjust should probably just be a positive/negative number
			//	passed through the SmartDashboard without the turnRight flag.
			//	Clockwise turns would be positive and CCW turns negative.
			//	Remove servo code, since it is used in the robot for other things
//			angleToAdjust = SmartDashboard::GetNumber(CAM_TURNANGLE, CAM_TURNANGLE_D);
//			turnRight = SmartDashboard::GetBoolean(CAM_TURNRIGHT, CAM_TURNRIGHT_D);
//			temp = RobotMap::shooterBallGate->GetAngle();
//			printf("!!! Original temp angle = %3f\n",temp);
//			if (turnRight == 1)
//				temp += angleToAdjust; //Turns right
//			else
//				temp -= angleToAdjust; //Turns left

//			printf("!!! Changed temp angle = %3f\n",temp);
//			RobotMap::shooterBallGate->SetAngle(temp);
//			SmartDashboard::PutNumber("Servo Angle", temp);
			SmartDashboard::PutBoolean(CAM_FOUNDTARGET, false);
		}
	}
#endif

}

void Robot::TestPeriodic() {
	lw->Run();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

//	Vision processing thread class

Robot::Robot():visionThread(CameraVisionThread) {
	m_faultsCleared = false;
	m_dashboardUpdate = 0;
}

// Vision processing thread

void Robot::CameraVisionThread() {
	// Declare vision thread variables
	float imgWidthFloat = (float)imgWidth;

	// Our camera input source - start it up
	cs::UsbCamera camera = CameraServer::GetInstance()->StartAutomaticCapture();
	camera.SetResolution(imgWidth, imgHeight);

	// Our vision processing pipeline
	grip::GripContoursPipeline cameraPipeline;

	// Our input/output stream - available to the dashboard (uses same resolution as input)
	cs::CvSink inputStream = CameraServer::GetInstance()->GetVideo();
	cs::CvSource outputStream = CameraServer::GetInstance()->PutVideo("Contours Video", imgWidth, imgHeight);

	// OpenCV structures for processing vision frames
	cv::Mat inputFrame;
	cv::Mat processFrame;

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

	//Flag for SmartDashboard if rectContours are found
	SmartDashboard::PutBoolean(CAM_FOUNDTARGET, false);  // initialize

	// Get the current brightness and exposure from the dashboard
	camera.SetBrightness((int) SmartDashboard::GetNumber(CAM_BRIGHTNESS, CAM_BRIGHTNESS_D));
	camera.SetExposureManual((int) SmartDashboard::GetNumber(CAM_EXPOSURE, CAM_EXPOSURE_D));

	// Main loop for our vision thread
	while (true) {
		static bool pipeEnabled = false;

		// DEBUG ONLY: Wait one second before starting each processing loop
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

		// Get a frame from the camera input stream
		inputStream.GrabFrame(inputFrame);

		// If the pipelineOn is false, then 'continue' will take camera out of the pipeline
		if (!SmartDashboard::GetBoolean(CAM_GEARPIPEON, false))
		{
			// If pipe was enabled, reset brightness and exposure
			if (pipeEnabled)
			{
				pipeEnabled = false;
				printf("2135: Gear Pipeline Off\n");
				// Get to a user visible brigntness and exposure
				camera.SetBrightness(100);
				camera.SetExposureAuto();
				camera.SetWhiteBalanceAuto();
			}

			//bypass pipeline
			continue;
		}
		else
		{
			// If pipe was disabled, set brightness and exposure for pipeline from dashboard
			if (!pipeEnabled)
			{
				pipeEnabled = true;
				printf("2135: Gear Pipeline On\n");
				// Get the current brightness and exposure from the dashboard
				camera.SetBrightness((int) SmartDashboard::GetNumber(CAM_BRIGHTNESS, CAM_BRIGHTNESS_D));
				camera.SetExposureManual((int) SmartDashboard::GetNumber(CAM_EXPOSURE, CAM_EXPOSURE_D));
			}
		}

		// Run vision processing pipeline generated from GRIP
		cameraPipeline.Process(inputFrame);
		// Get a reference to the pipeline output frame
		processFrame = *(cameraPipeline.gethslThresholdOutput());

		// Get a reference to the pipeline output contours
		std::vector<std::vector<cv::Point> >* filterContours = cameraPipeline.getfilterContoursOutput();

		// Declare a temporary holding list for validated rects
		std::vector<cv::Rect> validRectList;

		// Match flag initialization
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
			float rectRatio = ((float)rect.width / (float)rect.height) * 5.0/2.0;

			// If the rect is the correct rectangle target shape, save it in the hold list
			if ((rectRatio > 0.5) && (rectRatio < 2.0)) {
//				printf("2135: Boundary Rect in Hold List: %d\n", validRectList.size());
				printf("---> X = %d, Y = %d, W = %d, H = %d\n", rect.x, rect.y, rect.width, rect.height);
				validRectList.push_back(rect);

				// Finding the distance from the camera to the peg targets - individual rect (in)
// TEST				float pegRectDistance = Robot::CalcDistToTarget((float)2.0 , imgWidthFloat, (float)rect.width);
// TEST				printf("======= Rect Distance to Peg: %3f\n", pegRectDistance);
			}
		}

		// Print the number of valid rects stored in list
//		printf("2135: Boundary rects in list: %d\n", validRectList.size());

		if (validRectList.size() == 1) {
			// Find the adjustment angle to align this rectangle to the center of the frame
			cv::Rect& rect = validRectList[0];

			float rectDistance = Robot::CalcDistToTarget((float)2.0 , imgWidthFloat, (float)rect.width);
			printf("======= Rect Distance to Peg: %3f\n", rectDistance);

			float rectAngleAdjust = Robot::CalcCenteringAngle(rect, imgWidthFloat, rectDistance, 2.0);
			printf("::::::::: Angle to Adjust SingleRect %3f \n", rectAngleAdjust);
			SmartDashboard::PutNumber(CAM_TURNANGLE, rectAngleAdjust);
			SmartDashboard::PutBoolean(CAM_FOUNDTARGET, true);
			// TODO: Use this distance and angle to move the robot to center the target on the frame
		}
		// Need two contours in the hold list in order to make a group
		else if (validRectList.size() > 1) {
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

					// Set up a contour with the list of points to get a bounding rect surrounding both
					groupPoints.push_back(cv::Point(rectA.x, rectA.y));
					groupPoints.push_back(cv::Point(rectA.x, rectA.y + rectA.height));
					groupPoints.push_back(cv::Point(rectA.x + rectA.width, rectA.y + rectA.height));
					groupPoints.push_back(cv::Point(rectA.x + rectA.width, rectA.y));
					groupPoints.push_back(cv::Point(rectB.x, rectB.y));
					groupPoints.push_back(cv::Point(rectB.x, rectB.y + rectB.height));
					groupPoints.push_back(cv::Point(rectB.x + rectB.width, rectB.y + rectB.height));
					groupPoints.push_back(cv::Point(rectB.x + rectB.width, rectB.y));

					// Get the boundingRect around both valid individual targets
					cv::Rect groupRect = cv::boundingRect(groupPoints);

					// Checking the groupRect height:width ratio to verify bounding Rect
					float groupRectRatio = (((float)groupRect.width / (float)groupRect.height) * (5.0 / 10.25));

					// Validate the grouped targets as being of the correct aspect ratio
					if ((groupRectRatio > 0.5) && (groupRectRatio < 2.0)) {
						// Found a possible match
		//TEST				printf("!!! ---> 2135: Found a group ratio: %3f\n", groupRectRatio);
						printf("Group ---> X = %d, Y = %d, W = %d, H = %d\n", groupRect.x, groupRect.y, groupRect.width, groupRect.height);
						// Finding the distance from the camera to the peg - group rect (in)
						float pegGroupDistance = Robot::CalcDistToTarget((float)10.25 , imgWidthFloat, (float)groupRect.width);
						printf("======= Group Rect Distance to Peg: %3f\n", pegGroupDistance);

						// Add the valid group rect to the frame being processed
						cv::rectangle(processFrame, groupRect, cv::Scalar(0, 0, 255));
						foundMatch = true;

						float groupAngleAdjust = Robot::CalcCenteringAngle(groupRect, imgWidthFloat, pegGroupDistance, 10.25);
						printf("::::::::: Group Angle to Adjust %3f\n", groupAngleAdjust);
						//TODO: Use this data to drive the robot
						SmartDashboard::PutNumber(CAM_TURNANGLE, groupAngleAdjust);
						SmartDashboard::PutBoolean(CAM_FOUNDTARGET, true);
		//TEST				printf("---> 2135: Group rect height: %d, width: %d, x: %d, y: %d\n", groupRect.height, groupRect.width, groupRect.x, groupRect.y);
						break;
					}
					else continue;
				} // End itr2

				if (foundMatch) {
					break;
				}
			} // End itr1
			outputStream.PutFrame(processFrame);
		}
	}
}

float Robot::CalcDistToTarget(const float& rectWidthInches, const float& FOVPixels, const float& rectWidthPixels) {
	// Calculate the distance to the target given
	// RectWidthInches * FOVpixels / (2 * RectWidthPixels * tan(25 degrees)
	// Only need to change horizontal FOV angle here
	double FOVangle = 25.0;									// Using FOV horizontal angle = 25 degrees
	double angleRadian = FOVangle * 3.1415 / 180.0;			// Convert angle to radians
	return ((rectWidthInches * FOVPixels) / (2.0 * rectWidthPixels * (float)tan(angleRadian)));
}

float Robot::CalcCenteringAngle(const cv::Rect& rect, const float& imgWidthScreen, const float& distToTarget, const float& RectWidthInches) {
	float pixelsToCenter;
	float rectCenterX = (float)rect.x + (float)(rect.width)/2.0;

	// Determine if the rectangle needs to go left or right to align the peg to the center of the screen
	pixelsToCenter = rectCenterX - imgWidthScreen/2.0;


	// Get the inches to center by finding out the missing values from a target width
	float inchesToCenter = RectWidthInches * pixelsToCenter / (float)(rect.width);
	// Get the radians you have to turn to get to align the peg with the center of the screen by using the inverse of tan.
	float angleToAdjustRadians = (float)atan(inchesToCenter / distToTarget);
	// Convert the radians to degrees
	float angleToAdjustDegrees = angleToAdjustRadians * 180.0 / 3.1415;
	return angleToAdjustDegrees;
}

// Toggle mode for enabling/disabling the pipelines on the cameras for gear and shooter.

void Robot::VisionGearPipeOn() {
	SmartDashboard::PutBoolean(CAM_GEARPIPEON, true);
}

void Robot::VisionShooterPipeOn() {
	SmartDashboard::PutBoolean(CAM_SHOOTERPIPEON, true);
}

void Robot::VisionAllPipesOff() {
	SmartDashboard::PutBoolean(CAM_GEARPIPEON, false);
	SmartDashboard::PutBoolean(CAM_SHOOTERPIPEON, false);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

//	Preference handling utilities

double Robot::LoadPreferencesVariable(std::string name, double defaultValue) {
	double value;
	Preferences *prefs;

	prefs = frc::Preferences::GetInstance();

	if (prefs->ContainsKey(name)) {
		value = prefs->GetDouble(name, defaultValue);
		printf("2135: PREF    %-30s : %6.3f\n", name.c_str(), value);
	}
	else {
		value = defaultValue;
		printf("2135: ERROR - %-30s not found\n", name.c_str());
	}

	return value;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

//	Fault handling utilities

void Robot::HandleFaults(void) {
	printf("2135: %s --------------\n", "TALON SRX FAULTS");
	TalonSRXPrintFaults("chassisMotorL1", RobotMap::chassisMotorL1);
	TalonSRXPrintFaults("chassisMotorL2", RobotMap::chassisMotorL2);
	TalonSRXPrintFaults("chassisMotorR3", RobotMap::chassisMotorR3);
	TalonSRXPrintFaults("chassisMotorR4", RobotMap::chassisMotorR4);
	TalonSRXPrintFaults("intakeMotor8", RobotMap::intakeMotor8);
	TalonSRXPrintFaults("intakeMotor9", RobotMap::intakeMotor9);
	TalonSRXPrintFaults("agitatorMotor12", RobotMap::agitatorMotor12);
	TalonSRXPrintFaults("shooterMotor14", RobotMap::shooterMotor14);
	TalonSRXPrintFaults("climberMotor18", RobotMap::climberMotor18);
	TalonSRXPrintFaults("climberMotor19", RobotMap::climberMotor19);

	printf("2135: %s --------------\n", "PCM FAULTS");
	if (RobotMap::pneumaticsCompressor->GetCompressorCurrentTooHighStickyFault())
		printf("\tCurrentTooHighFault\n");
	if (RobotMap::pneumaticsCompressor->GetCompressorNotConnectedFault())
		printf("\tCompressorNotConnectedFault\n");
	if (RobotMap::pneumaticsCompressor->GetCompressorShortedFault())
		printf("\tCompressorShortedFault\n");
	RobotMap::pneumaticsCompressor->ClearAllPCMStickyFaults();

	printf("2135: %s --------------\n", "PDP FAULTS");
	RobotMap::powerPDP->ClearStickyFaults();

	//faults
}

void Robot::TalonSRXPrintFaults(const char *talonName, std::shared_ptr<CANTalon> talonPtr) {

	uint16_t	faults;
	uint16_t	stickyFaults;

	faults = talonPtr->GetFaults();
	stickyFaults = talonPtr->GetStickyFaults();
	talonPtr->ClearStickyFaults();

	printf("2135: %s --------------\n", talonName);

	if (faults & CANTalon::kTemperatureFault)
		printf("\tkTemperatureFault\n");
	if (faults & CANTalon::kBusVoltageFault)
		printf("\tkBusVoltageFault\n");
	if (faults & CANTalon::kFwdLimitSwitch)
		printf("\tkFwdLimitSwitch\n");
	if (faults & CANTalon::kRevLimitSwitch)
		printf("\tkRevLimitSwitch\n");
	if (faults & CANTalon::kFwdSoftLimit)
		printf("\tkFwdLimitSwitch\n");
	if (faults & CANTalon::kRevSoftLimit)
		printf("\tkRevLimitSwitch\n");

	if (stickyFaults & CANTalon::kTemperatureFault)
		printf("\tSticky - kTemperatureFault\n");
	if (stickyFaults & CANTalon::kBusVoltageFault)
		printf("\tSticky - kBusVoltageFault\n");
	if (stickyFaults & CANTalon::kFwdLimitSwitch)
		printf("\tSticky - kFwdLimitSwitch\n");
	if (stickyFaults & CANTalon::kRevLimitSwitch)
		printf("\tSticky - kRevLimitSwitch\n");
	if (stickyFaults & CANTalon::kFwdSoftLimit)
		printf("\tSticky - kFwdLimitSwitch\n");
	if (stickyFaults & CANTalon::kRevSoftLimit)
		printf("\tSticky - kRevLimitSwitch\n");
}

START_ROBOT_CLASS(Robot);

