/*
 * VisionThread.h
 *
 *  Created on: Aug 6, 2017
 *      Author: PHS_User
 */

#ifndef SRC_VISIONPIPELINE_H_
#define SRC_VISIONPIPELINE_H_

#include <frc/SmartDashboard/SmartDashboard.h>
#include "RobotDefaults.h"
#include "frc2135/GripContoursPipeline.h"

class VisionPipeline {
private:
	struct pixelRect {				// Vision rectangle of pixels
		int 	width;
		int 	height;
	};
	struct pixelRect m_res;			// Initial camera resolution
	struct dimRect {				// Actual vision target dimensions - inches
		double width;
		double height;
	};
	struct dimRect m_targSize;		// Vision Target dimensions
	struct dimRect m_hatchSize;		// Vision Hatch target dimensions
	typedef struct targetData {		// Validated Target data (or Hatch data)
		cv::Rect	r;				// Target rect in pixel coordinates
		bool 		bSlantRight; 
		double		score;			// Target score as compared to theoretical
		double		dist;			// Calculated distance to target
		double		angle;			// Calculated angle to target
	} tData;

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

	std::shared_ptr<NetworkTable> m_netTable;

	void InitializeSmartdashboard(void);
	void SetCamConfig(cs::UsbCamera cam);
	void ConfigureCamera(cs::UsbCamera cam, int resWidth, int resHeight, int fps, int bright, int expos);
	bool DetermineSlant(cv::RotatedRect *rotRect);
	void ConvertContoursToBoundingRects(std::vector<std::vector<cv::Point>> *contours, std::vector<tData> *rawData);
	void ConvertBoundingRectsToValidTargets(std::vector<tData> *rawData, std::vector<tData> *targets);
	void ConvertValidTargetsToValidHatches(std::vector<tData> *targets, std::vector<tData> *hatches);
	void SortValidHatches(std::vector<tData> *targets);
	void PrintTargetData(char name, int idx, tData t);
	void ApplyGridToFrame(cv::Mat frame, pixelRect res /*,double dist, double angle*/);
	void ApplyRectsToFrame(cv::Mat frame, std::vector<tData> *targets);
	void ApplyHatchesToFrame(cv::Mat frame, std::vector<tData> *hatches);
	double CalcInchesToTarget(double targetWidthInches, cv::Rect rect);
	double CalcCenteringAngle(double targetWidthInches, cv::Rect rect, double inchesToTarget);
	void ChooseGoalHatch(std::vector<tData> *hatches, tData *goal);
	void ApplyGoalToFrame(cv::Mat frame, tData goal);

public:
	VisionPipeline();
	virtual ~VisionPipeline();
	void Init();
	void Process(cv::Mat inFrame);

};

#endif /* SRC_VISIONPIPELINE_H_ */
