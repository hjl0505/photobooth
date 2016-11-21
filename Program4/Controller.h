#include <opencv2/highgui/highgui.hpp>
#include "ItemOverlay.h"

using namespace cv;

#pragma once
class Controller
{
public:
	Controller();
	
	Mat& controls(Mat& image, char key);
private:
	char currentItem; // 1: hat, 2: glasses, 3: mustache
};

