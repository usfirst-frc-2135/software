/*
 * VisionThread.h
 *
 *  Created on: Aug 6, 2017
 *      Author: PHS_User
 */

#ifndef SRC_VISIONLOOP_H_
#define SRC_VISIONLOOP_H_

#include "RobotDefaults.h"
#include "GripContoursPipeline.h"

class VisionLoop {
private:
	struct resRect {
		int width;
		int height;
	};
	struct resRect res;				// Initial camera resolution
	struct resRect m_targSize;		// Vision Target dimensions
	struct resRect m_pegSize;		// Vision Target dimensions

	std::shared_ptr<NetworkTable> table;

	void InitializeSmartdashboard(void);
	void ConfigureCamera(cs::UsbCamera cam, int resWidth, int resHeight, int fps, int bright, int expos);
	void ConvertContoursToBoundingRects(std::vector<std::vector<cv::Point>> *contours, std::vector<cv::Rect> *rects);
	double ConvertBoundingRectsToValidTargets(std::vector<cv::Rect> *rects, std::vector<cv::Rect> *targets);
	double ConvertValidTargetsToValidPegs(std::vector<cv::Rect> *targets, std::vector<cv::Rect> *pegs);
	void ApplyRectsToFrame(cv::Mat frame, std::vector<cv::Rect> rects);
	double CalcInchesToTarget(double targetWidthInches, cv::Rect rect);
	double CalcCenteringAngle(double targetWidthInches, cv::Rect rect, double inchesToTarget);

public:
	VisionLoop();
	virtual ~VisionLoop();
	void Run();

	void VisionGearPipeOn();
	void VisionShooterPipeOn();
	void VisionAllPipesOff();

};

#endif /* SRC_VISIONLOOP_H_ */
