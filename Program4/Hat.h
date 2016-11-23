#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#pragma once
class Hat
{
public:
	Hat();

	void putHat(Mat& image, int x, int y);

private:
	void convertBW(Mat& binaryHat, Mat& colorHat);

	int currentHat;

	Mat hat1;
	Mat hat2;
};

