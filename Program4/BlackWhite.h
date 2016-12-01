// BlackWhite.h
// Chris Knakal and Hyungjin Lee
// CSS 487 Program 4 -- Photobooth
// 11.19.2016
//
// Converts image into greyscale image, except for selected color (black, red, blue, green)
// If color Black is selected, it shows regular greyscale image.

#include <opencv2/highgui/highgui.hpp>
#include "ItemOverlay.h"
#include "FaceRecognition.h"

using namespace cv;
using namespace std;

#pragma once

class BlackWhite
{
public:
	// Constructor
	BlackWhite();

	// Functions
	void makeBW(Mat& image);
	void nextColor();
	void lastColor();

private:
	// Helper Functions
	void thresholdImage(Mat& imgHSV, Mat& image);

	// Variables
	const int COLOR_COUNT = 4; // total number of threshold colors available
	int currentColor; // 0:black 1:red 2:blue 3:green 
};

