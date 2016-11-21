#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

#pragma once
class Controller
{
public:
	Controller();
	
	Mat& controls(Mat& image, char key);
private:
	char currentItem; // 1: hat, 2: glasses, 3: mustache
	int currentOption; // e.g. different type of mustache
};

