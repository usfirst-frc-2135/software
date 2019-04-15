// visiontest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <fstream>

#include "GripContoursPipeline.h"
#include "GripOuterPipeline.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	ifstream filelist;		// File containing list of images to process
	char curpathname[256];
    char curfilename[256];
	Mat image;
	cv::Mat gripFrame;
    double goalDist;
    double goalAngle;
    double goalPose;

	std::unique_ptr<grip::GripOuterPipeline> gripPipe;
	gripPipe.reset(new grip::GripOuterPipeline());

	std::cout << "FRC Team 2135 - Vision Test Harness\n";

	// Test OpenCV Logo image to start out
	image = imread("./OpenCV_Logo_with_text.png", IMREAD_COLOR); // Read the file
	if (image.empty()) // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	namedWindow("OpenCV Logo", WINDOW_NORMAL);
    resizeWindow("OpenCV Logo", 300, 370);
	imshow("OpenCV Logo", image);
	waitKey(0);			// Wait for a keystroke in the window
    destroyWindow("OpenCV Logo");

	// Open the file containing the list of FRC images
	filelist.open("./frcimagelist.txt", std::ifstream::in);
	do {
        int i;

		// Retrieve each file name -- one per line
		filelist.getline(curpathname, sizeof(curpathname));
        for (i = 0; i < sizeof(curpathname); i++)
            if (curpathname[i] == '/' || curpathname[i] == '\0')
                break;
        strcpy(curfilename, curpathname+i+1);
        cout << curpathname << " -> " << curfilename << std::endl;

		// Open the image file specified
		image = imread(curpathname, IMREAD_COLOR); // Read the file
		if (image.empty()) // Check for invalid input
		{
			cout << "Could not open or find the image" << std::endl;
			return -1;
		}

		// Open a new window with using the file name as the title
		namedWindow(curfilename, WINDOW_AUTOSIZE); // Create a window for display.
        moveWindow(curfilename, 20, 20);
		imshow(curfilename, image); // Show our image inside it.

		// Call GripPipeline
		// Run vision processing gripPipe generated from GRIP
		gripPipe->Process(image);
        gripPipe->GetGoalHatch(&goalDist, &goalAngle, &goalPose);

		cout << "Goal Hatch -> d " << goalDist << " a " << goalAngle << " p " << goalPose << std::endl;

		// Call GoalPipeline

		waitKey(0); // Wait for a keystroke in the window

		// Clean up and close the window
		destroyWindow(curfilename);

	} while (!filelist.eof());

	cout << "All images processed -- Enter any key to close" << std::endl;
	waitKey(0); // Wait for a keystroke in the window
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
