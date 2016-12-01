// Glasses.h
// Chris Knakal and Hyungjin Lee
// CSS 487 Program 4 -- Photobooth
// 11.19.2016
//
// Draws a pair of glasses on the input image

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

const int GLASSES_COUNT = 3; // Total number of different glasses available

#pragma once
class Glasses
{
public:
	// Constructor
	Glasses();

	// Functions
	void putGlasses(Mat& image, int x, int y, int colors[]);
	void scaleGlasses(int width, int height);
	void nextOption();
	void lastOption();

private:
	// Helper Functions
	void convertBW(Mat& binaryGlasses, Mat& colorGlasses);

	// Variables 
	int currentGlassesIndex; // index of glasses in glasses array
	Mat currentScaledGlasses; // current scaled hat to draw
	Mat glasses[GLASSES_COUNT]; // glasses array of all available glasses
};

