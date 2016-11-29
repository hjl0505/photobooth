
#include <opencv2/highgui/highgui.hpp>
#include "ItemOverlay.h"
#include "FaceRecognition.h"
#include <iostream>

using namespace cv;
using namespace std;

#pragma once
class FaceSwap
{
public:
	void swap();

private:
	void swapHelper(Mat& face1, Mat& face2);
};

