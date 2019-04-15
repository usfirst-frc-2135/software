/*
 * GripOuterPipeline.cpp
 *
 *  Created on: Aug 6, 2017
 *      Author: PHS_User
 */

#include "GripOuterPipeline.h"

#ifdef _MSC_VER
#define DEBUG_TRACE 2       // Set to 1 for detailed tracing, 0 for quiet mode
#else
#define DEBUG_TRACE 0       // Default debuggging messsages off when embedded
#endif

namespace grip
{

GripOuterPipeline::GripOuterPipeline()
{
	std::printf("2135: GripOuterPipeline Constructor\n");

	m_res.width = 320;
	m_res.height = 240;

	m_targSize.width = 3.313;					// 2019 Vision target dimensions
	m_targSize.height = 5.826;
	m_hatchSize.width = 14.626;					// 2019 Hatch (two targets) dimensions
	m_hatchSize.height = 5.826;

	// Start our GRIP-generated vision processing pipeline
	m_gripPipe = new GripContoursPipeline();

	// Set our input/output stream - available to the dashboard (same resolution as input)
#ifndef _MSC_VER	// Compiled for Windows
	m_outStream = frc::CameraServer::GetInstance()->PutVideo("Goal Video", m_res.width, m_res.height);
#endif
}

GripOuterPipeline::~GripOuterPipeline()
{
	// Auto-generated destructor stub
}

void GripOuterPipeline::Process(cv::Mat &source0)
{
	//std::printf("2135: GripOuterPipeline Process\n");

	// Run vision processing m_gripPipe generated from GRIP
	m_gripPipe->Process(source0);
	m_gripFrame = *(m_gripPipe->GetHslThresholdOutput());
	m_contours = m_gripPipe->GetFilterContoursOutput();

	ConvertContoursToBoundingRects(m_contours, &m_boundingRects);
	ConvertBoundingRectsToValidTargets(&m_boundingRects, &m_validTargets);
	ConvertValidTargetsToValidHatches(&m_validTargets, &m_validHatches);
	SortValidHatches(&m_validHatches);
	ChooseGoalHatch(&m_validHatches, &m_goal);

#if DEBUG_TRACE > 0
	std::printf("2135: C %d, B %d, T %d, H %d, G %d, x %d, y %d, w %d, h %d, d %5.1f, a %5.1f\n",
		(int) m_contours->size(), (int) m_boundingRects.size(), (int) m_validTargets.size(), (int) m_validHatches.size(),
		(m_validHatches.size() > 0) ? 1 : 0, m_goal.r.x, m_goal.r.y, m_goal.r.width, m_goal.r.height, m_goal.dist, m_goal.angle);
#endif

	// Draw the boundingRects on the frame bring processed -- white
	ApplyGridToFrame(source0, m_res);
	ApplyRectsToFrame(source0, &m_validTargets);
	ApplyHatchesToFrame(source0, &m_validHatches);
	ApplyGoalToFrame(source0, m_res, m_goal);

#ifdef _MSC_VER	// Compiled for Windows
	// Draw the boundingRects on the frame bring processed -- white
	ApplyGridToFrame(m_gripFrame, m_res);
	ApplyRectsToFrame(m_gripFrame, &m_validTargets);
	ApplyHatchesToFrame(m_gripFrame, &m_validHatches);
	ApplyGoalToFrame(m_gripFrame, m_res, m_goal);
    cv::namedWindow("Grip Frame");
    cv::moveWindow("Grip Frame", 20, 300);
    imshow("Grip Frame", m_gripFrame);

    cv::namedWindow("Source Frame");
    cv::moveWindow("Source Frame", 360, 300);
    imshow("Source Frame", source0);
#else	// Compiled for embedded platform
    m_outStream.PutFrame(source0);
#endif

}

void GripOuterPipeline::ConvertContoursToBoundingRects(std::vector<std::vector<cv::Point>> *contours, std::vector<tData> *rects)
{
    rects->clear();

    // If contours are available, loop through up to 8 of them and create a vector of bounding rects
    if (!m_contours->empty())
    {
        for (uint32_t i = 0; i < m_contours->size() && i < 8; i++)
        {
            tData rawt;
            double  slantAngle;

            rawt.r = cv::boundingRect(m_contours->at(i));
            cv::RotatedRect rotRect = cv::minAreaRect(m_contours->at(i));
            slantAngle = (rotRect.size.width < rotRect.size.height) ? rotRect.angle : rotRect.angle + 90.0;
            rawt.bSlantRight = (slantAngle > 0);
            rects->push_back(rawt);
        }
    }
}

void GripOuterPipeline::ConvertBoundingRectsToValidTargets(std::vector<tData> *rects, std::vector<tData> *targets)
{
    const double    scoreMin = 50.0;
    const double    scoreMax = 150.0;
	double	score;
	tData t;

	targets->clear();

	// If boundingRects are available, loop through them and create a vector of valid targets
	if (!rects->empty())
	{
		for (uint32_t i = 0; i < rects->size(); i++)
		{
			cv::Rect r = rects->at(i).r;

			// Translate width and height to floating point and calculate normalized score 0..100
			score = 100 * ((double)r.width / (double)r.height) * (m_targSize.height / m_targSize.width);

			// If the bounding rect score is close to 100, save it in the hold list
			if ((score > scoreMin) && (score < scoreMax))
			{
				t.r = r;
				t.score = score;
				t.dist = CalcInchesToTarget(m_targSize.width, r);
				t.angle = CalcCenteringAngle(m_targSize.width, r, t.dist);
				t.bSlantRight = rects->at(i).bSlantRight;
				targets->push_back(t);
                PrintTargetData('T', i, t);
            }
		}
	}
}

void GripOuterPipeline::ConvertValidTargetsToValidHatches(std::vector<tData> *targets, std::vector<tData> *hatches)
{
    const double    scoreMin = 50.0;
    const double    scoreMax = 150.0;
    double 	score;
	tData	h;

	hatches->clear();

	// If any validTargets are available, loop through them and create a vector of valid hatches
	if (targets->size() >= 2)
	{
		for (uint32_t i = 0; i < targets->size() - 1; i++)
		{
			cv::Rect targA = targets->at(i).r;

			for (uint32_t j = i + 1; j < targets->size(); j++)
			{
				cv::Rect targB = targets->at(j).r;

				// Determine whether A or B is the leftmost target.
				tData leftMost = targets->at(i); 
				tData rightMost = targets->at(j); 

				if (targA.tl().x > targB.tl().x)
				{
					leftMost = targets->at(j);
					rightMost = targets->at(i);
				}

				// Invalid if left target is slanted left OR right target is slanted right
				if (!leftMost.bSlantRight || rightMost.bSlantRight)
					continue;

				// Build a virtual contour around RectA and RectB (use top left/bottom right)
				std::vector<cv::Point> hatchPoints;
				hatchPoints.push_back(targA.tl());
				hatchPoints.push_back(targA.br());
				hatchPoints.push_back(targB.tl());
				hatchPoints.push_back(targB.br());
				cv::Rect hatchRect = cv::boundingRect(hatchPoints);

				// Translate width and height to floating point and calculate normalized score 0..100
				score = 100 * (((double)hatchRect.width / (double)hatchRect.height) * (m_hatchSize.height / m_hatchSize.width));

				// If the bounding rect score is close to 100, save it in the hold list
				if ((score > scoreMin) && (score < scoreMax))
				{
					// Finding the distance from the camera to the hatch - group rect (in)
					h.r = hatchRect;
					h.score = score;
					h.dist = CalcInchesToTarget(m_hatchSize.width, hatchRect);
					h.angle = CalcCenteringAngle(m_hatchSize.width, hatchRect, h.dist);
					hatches->push_back(h);

                    PrintTargetData('H', i * 10 + j, h);
                }
            }
		}
	}
}

void GripOuterPipeline::SortValidHatches(std::vector<tData> *hatches)
{
	tData h;
	int size = (int) hatches->size();

	if (size > 0)
	{
	    int i;
	    int j;
	    tData key;

	    for (i = 1; i < size; i++)
	    {
		    key = hatches->at(i);
		    j = i-1;

		    while ((j >= 0) && (hatches->at(j).r.tl().x > key.r.tl().x))
		    {
			    hatches->at(j+1) = hatches->at(j);
			    j = j-1;
		    }
		    hatches->at(j+1) = key;
	    }
	}

	for (int i = 0; i < hatches->size(); i++)
	{
		h = hatches->at(i);
		PrintTargetData('S', i, h);
	}
}

void GripOuterPipeline::ChooseGoalHatch(std::vector<tData> *hatches, tData *goal)
{
//	goal = &(hatches->front());
    if (hatches->size() > 0)
        memcpy(goal, &(hatches->front()), sizeof(tData));
    else
        memset(goal, 0, sizeof(tData));
}

bool GripOuterPipeline::GetGoalHatch(double *goalDist, double *goalAngle, double *goalPose)
{
	*goalDist = m_goal.dist;
	*goalAngle = m_goal.angle;
	*goalPose = 0.0;
	return !m_validHatches.empty();
}

void GripOuterPipeline::PrintTargetData(char name, int idx, tData t)
{
#if DEBUG_TRACE > 1
	std::printf("-%c %02d: x %3d, y %3d, w %3d, h %3d, t %c, s %5.1f, d %5.1f, a %5.1f\n", name, idx,
	 	t.r.x, t.r.y, t.r.width, t.r.height, (t.bSlantRight) ? 'R' : 'L', t.score, t.dist, t.angle);
#endif
}

void GripOuterPipeline::ApplyGridToFrame(cv::Mat frame, pixelRect res)
{
	cv::Point	pt1, pt2;

	pt1.x = 0;
	pt2.x = res.width;
	pt1.y = pt2.y = res.height / 2;
	cv::line(frame, pt1, pt2, cv::Scalar(255, 255, 255), 1, cv::LineTypes::LINE_4, 0);

	pt1.y = 0;
	pt2.y = res.height;
	pt1.x = pt2.x = res.width / 2;
	cv::line(frame, pt1, pt2, cv::Scalar(255, 255, 255), 1, cv::LineTypes::LINE_4, 0);
}

void GripOuterPipeline::ApplyRectsToFrame(cv::Mat frame, std::vector<tData> *targets)
{
	for (uint32_t i = 0; i < targets->size(); i++)
	{
		cv::Rect& tRect = targets->at(i).r;
		cv::rectangle(frame, tRect, cv::Scalar(68, 68, 255), 2, cv::LineTypes::LINE_8);
	}
}

void GripOuterPipeline::ApplyHatchesToFrame(cv::Mat frame, std::vector<tData> *hatches)
{
	for (uint32_t i = 0; i < hatches->size(); i++)
	{
		tData& tHatch = hatches->at(i);

		cv::rectangle(frame, tHatch.r, cv::Scalar(0, 255, 255), 2, cv::LineTypes::LINE_8);
	}
}

void GripOuterPipeline::ApplyGoalToFrame(cv::Mat frame, pixelRect res, tData goal)
{
	cv::Point	pt1, pt2;
	char		str[32];

	cv::rectangle(frame, goal.r, cv::Scalar(0, 255, 0), 2, cv::LineTypes::LINE_8);

	pt1.x = goal.r.x + goal.r.width/2 - 5;
	pt2.x = pt1.x + 10;
	pt1.y = pt2.y = goal.r.y + goal.r.height/2;
	cv::line(frame, pt1, pt2, cv::Scalar(0, 255, 0), 1, cv::LineTypes::LINE_4, 0);

	pt1.y = goal.r.y + goal.r.height/2 - 5;
	pt2.y = pt1.y + 10;
	pt1.x = pt2.x = goal.r.x + goal.r.width/2;
	cv::line(frame, pt1, pt2, cv::Scalar(0, 255, 0), 1, cv::LineTypes::LINE_4, 0);

	std::sprintf(str, "%5.1f in", goal.dist);
	pt1.x = 5;
	pt1.y = res.height - 5;
	cv::putText(frame, str, pt1, cv::FONT_HERSHEY_DUPLEX, 1.0, cv::Scalar(255, 255, 255),
		1, cv::LineTypes::LINE_8, false);

	std::sprintf(str, "%5.1f deg", goal.angle);
	pt1.x = res.width/2 - 10;
	pt1.y = res.height - 5;
	cv::putText(frame, str, pt1, cv::FONT_HERSHEY_DUPLEX, 1.0, cv::Scalar(255, 255, 255),
		1, cv::LineTypes::LINE_8, false);
}

double GripOuterPipeline::CalcInchesToTarget(double targetWidthInches, cv::Rect rect)
{
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

double GripOuterPipeline::CalcCenteringAngle(double targetWidthInches, cv::Rect rect, double inchesToTarget)
{
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

} // namespace grip
