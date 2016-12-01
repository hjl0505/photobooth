// Controller.h
// Chris Knakal and Hyungjin Lee
// CSS 487 Program 4 -- Photobooth
// 11.19.2016
//
// Redirects user input to the appropriate functionalities of the photobooth

#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include "ItemOverlay.h"
#include "FaceRecognition.h"
#include "BlackWhite.h"
#include "FaceSwap.h"

using namespace cv;
using namespace std;

#pragma once
class Controller
{
public:
	// Constructor
	Controller();

	// Functions
	void controls(Mat& image, char key);

private:
	// Helper Functions
	void getHat(Mat& image);
	void getGlasses(Mat& image);
	void getMustache(Mat& image);
	void makeBW(Mat& image);
	void nextColor();
	void lastColor();
	
	// Variables
	char lastItemKey;

	FaceRecognition faceRec; // FaceRecognition class
	ItemOverlay over;
	BlackWhite blackWhite;
	FaceSwap swapper;
};

