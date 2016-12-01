#include <opencv2/highgui/highgui.hpp>
#include "FaceRecognition.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>



using namespace cv;
using namespace std;

#pragma once
class FaceSwap
{
public:
	void swap(Mat& image);

private:
	void swapHelper(Mat& image, Mat& tempImage, Rect faceTo, Rect faceFrom);

	int getFaceWidth(Mat& face);
	int getFaceHeight(Mat& face);
	bool insideFaceEllipse(Mat& image, Rect faceTo, int curX, int curY, Point toCenter);

	FaceRecognition faceRec;
};

