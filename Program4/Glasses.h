// Glasses.h
// Chris Knakal and Hyungjin Lee
// CSS 487 Program 4 -- Photobooth
// 11.19.2016
//
// Draws a pair of glasses on the input image

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

const int GLASSES_COUNT = 3;

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
	void convertBW(Mat& binaryHat, Mat& colorHat);

	// Variables 
	int currentGlassesIndex;
	Mat currentScaledGlasses;
	Mat glasses[GLASSES_COUNT];
};

