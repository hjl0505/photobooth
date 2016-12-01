// FaceSwap.h
// Chris Knakal and Hyungjin Lee
// CSS 487 Program 4 -- Photobooth
// 11.19.2016
//
// Attempts to swap two faces
// Uses rough oval shape to swap

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "FaceRecognition.h"

using namespace cv;
using namespace std;

#pragma once
class FaceSwap
{
public:
	// Functions
	void swap(Mat& image);

private:
	// Helper Functions
	void swapHelper(Mat& image, Mat& tempImage, Rect faceTo, Rect faceFrom);
	bool insideFaceEllipse(Mat& image, Rect faceTo, int curX, int curY, Point toCenter);
	int getFaceWidth(Mat& face);
	int getFaceHeight(Mat& face);

	// Variables
	FaceRecognition faceRec;
};

