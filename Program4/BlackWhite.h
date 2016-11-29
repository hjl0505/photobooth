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
	void makeBW(Mat& image);
};

