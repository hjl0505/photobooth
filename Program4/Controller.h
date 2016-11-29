// Controller.h
// Chris Knakal and Hyungjin Lee
// CSS 487 Program 4 -- Photobooth
// 11.19.2016
//
// Redirects user input to the appropriate functionalities of the photobooth

#include <opencv2/highgui/highgui.hpp>
#include "ItemOverlay.h"
#include "FaceRecognition.h"
#include <iostream>

using namespace cv;
using namespace std;

#pragma once
class Controller
{
public:
	// Functions
	void controls(Mat& image, char key);

private:
	// Helper Functions
	void getHat(Mat& image);
	void getGlasses(Mat& image);
	void getMustache(Mat& image);
	
	// Variables
	char lastItemKey = 0;

	FaceRecognition faceRec; // FaceRecognition class
	ItemOverlay over;
};

