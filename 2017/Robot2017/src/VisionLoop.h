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
	struct visRect {
		int width;
		int height;
	};
	struct visRect m_res;				// Initial camera resolution
	struct visRect m_targSize;		// Vision Target dimensions
	struct visRect m_pegSize;		// Vision Peg dimensions
	struct goal {
		cv::Rect r;
		double	score;
		double	dist;
		double	angle;
	};
	struct goal m_goal;

	std::shared_ptr<NetworkTable> m_netTable;

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
