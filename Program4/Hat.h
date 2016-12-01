// Hat.h
// Chris Knakal and Hyungjin Lee
// CSS 487 Program 4 -- Photobooth
// 11.19.2016
//
// Draws a hat on the input image

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

const int HAT_COUNT = 4; // Total number of different hats available

#pragma once
class Hat
{
public:
	// Constructor
	Hat();

	// Functions
	void putHat(Mat& image, int x, int y, int colors[]);
	void scaleHat(int width, int height);
	void nextOption();
	void lastOption();

private:
	// Helper Functions
	void convertBW(Mat& binaryHat, Mat& colorHat);
	
	// Variables 
	int currentHatIdx; // index of hat in hat array
	Mat currentScaledHat; // current scaled hat to draw
	Mat hats[HAT_COUNT]; // hat array of all available hats
};

