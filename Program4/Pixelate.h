// Pixelate.h
// Chris Knakal and Hyungjin Lee
// CSS 487 Program 4 -- Photobooth
// 11.19.2016
//
// Pixelates Faces by varying degrees

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

#pragma once

class Pixelate
{
public:
	// Constructor
	Pixelate();

	// Functions
	void nextOption();
	void lastOption();

private:
	// Helper Functions
	void pixelateFace(Mat& image, Rect face);
	void getAvgBlockColor(Mat& image, Rect face, int row, int col, int& blueTot, int& greenTot, int& redTot);

	// Variables
	int divisions; //determines the pixelated block size
};

