// Mustache.h
// Chris Knakal and Hyungjin Lee
// CSS 487 Program 4 -- Photobooth
// 11.19.2016
//
// Draws a mustache on the input image

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

const int MUSTACHE_COUNT = 7;

#pragma once
class Mustache
{
public:
	// Constructor
	Mustache();

	// Functions
	void putMustache(Mat& image, int x, int y, int colors[]);
	void scaleMustache(int width, int height);

	void nextOption();
	void lastOption();

private:
	// Helper Functions
	void convertBW(Mat& binaryMustache, Mat& colorMustache);

	// Variables 
	int currentMustacheIndex;
	Mat currentScaledMustache;
	Mat mustache[MUSTACHE_COUNT];
};