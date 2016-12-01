#pragma once
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#pragma once

class Pixelate
{
public:
	Pixelate();
	void pixelator(Mat& image, Rect face);
	void nextOption();
	void lastOption();

private:
	int totalPixels;
	int divisions;

	void getAvgBlockColor(Mat& image, Rect face, int row, int col, int& blueTot, int& greenTot, int& redTot);
};

