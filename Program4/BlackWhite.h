#include <opencv2/highgui/highgui.hpp>
#include "ItemOverlay.h"
#include "FaceRecognition.h"
#include <iostream>

using namespace cv;
using namespace std;

#pragma once
class BlackWhite
{
public:
	BlackWhite();

	void makeBW(Mat& image);
	void nextColor();
	void lastColor();

private:
	void thresholdImage(Mat& imgHSV, Mat& image);

	const int COLOR_COUNT = 4;
	int currentColor; // 0:black 1:red 2:blue ...etc 
};

