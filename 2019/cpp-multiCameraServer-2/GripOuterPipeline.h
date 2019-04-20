 /*
 * GripOuterPipeline.h
 *
 *  Created on: Aug 6, 2017
 *      Author: PHS_User
 */

#pragma once

#include "RobotDefaults.h"

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <string>
#include <math.h>

#include "GripContoursPipeline.h"

namespace grip
{

class GripOuterPipeline : public frc::VisionPipeline
{
  private:
	struct pixelRect
	{ // Vision rectangle of pixels
		int width;
		int height;
	};
	struct pixelRect m_res; // Initial camera resolution

	struct dimRect
	{ // Actual vision target dimensions - inches
		double width;
		double height;
	};
	struct dimRect m_targSize;  // Vision Target dimensions
	struct dimRect m_hatchSize; // Vision Hatch target dimensions

	typedef struct targetData
	{				        // Validated Target data (or Hatch data)
		cv::Rect r;         // Target rect in pixel coordinates
        cv::RotatedRect rRot;       // Rotated target rect using minAreaRect
		bool bSlantRight;
		double score;       // Target score as compared to theoretical
		double dist;        // Calculated distance to target
		double yawAngle;    // Calculated angle to target
        double faceAngle;   // Calculated target face angle from normal
	} tData;

	// Inner Grip pipeline variables
	GripContoursPipeline 	*m_gripPipe;
	cv::Mat 				m_gripFrame;

	// CameraServer structures for processing vision frames
#ifndef _MSC_VER	// Compiled for Windows
	cs::CvSource 			m_outStream;
#endif

	// Image processing structures for identifying targets and hatches
	std::vector<std::vector<cv::Point>> *m_contours;
	std::vector<tData> 		m_boundingRects;
	std::vector<tData> 		m_validTargets;
	std::vector<tData> 		m_validHatches;
	tData 					m_goal;

	void ConvertContoursToBoundingRects(std::vector<std::vector<cv::Point>> *contours, std::vector<tData> *rawData);
	void ConvertBoundingRectsToValidTargets(std::vector<tData> *rawData, std::vector<tData> *targets);
	void ConvertValidTargetsToValidHatches(std::vector<tData> *targets, std::vector<tData> *hatches);
	void SortValidHatches(std::vector<tData> *targets);
	void ChooseGoalHatch(std::vector<tData> *hatches, tData *goal);
	void PrintTargetData(char name, int idx, tData t);

	void ApplyGridToFrame(cv::Mat frame, pixelRect res);
	void ApplyRectsToFrame(cv::Mat frame, std::vector<tData> *targets);
	void ApplyHatchesToFrame(cv::Mat frame, std::vector<tData> *hatches);
	void ApplyGoalToFrame(cv::Mat frame, pixelRect res, tData goal);
	double CalcInchesToTarget(double targetWidthInches, cv::Rect rect);
	double CalcYawAngle(double targetWidthInches, cv::Rect rect, double inchesToTarget);

  public:
	GripOuterPipeline();
	virtual ~GripOuterPipeline();
	virtual void Process(cv::Mat &source0);
	bool GetGoalHatch(double *goalDist, double *goalYawAngle, double *goalFaceAngle);
};

} // namespace grip
