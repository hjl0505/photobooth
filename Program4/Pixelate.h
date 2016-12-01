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
	void Pixelate::pixelator(Mat& image, Rect face);

private:
	int totalPixels;
	int divisions;
};

