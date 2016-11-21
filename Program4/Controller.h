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
	Controller();
	
	void controls(Mat& image, char key);

private:
	void getHat(Mat& image, char key);
	void getGlasses(Mat& image, char key);
	void getMustache(Mat& image, char key);
	
	FaceRecognition faceRec; // FaceRecognition class
	ItemOverlay over;
};

