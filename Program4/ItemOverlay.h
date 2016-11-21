#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#pragma once

class ItemOverlay
{
public:
	ItemOverlay();

	void putHat(Mat& image, vector<Rect_<int>> faces);
	void putGlasses(Mat& image, vector<Rect_<int>> faces);
	void putMustache(Mat& image, vector<Rect_<int>> faces);

	void nextColor(Mat& image);
	void lastColor(Mat& image);
	void nextOption(Mat& image);
	void lastOption(Mat& image);


private:
	const int COLOR_COUNT = 6;
	const int HAT_COUNT = 2;
	const int GLASSES_COUNT = 2;
	const int MUSTACHE_COUNT = 5;
	
	int[][] colorChart;
	char currentItem; // 1: hat, 2: glasses, 3: mustache
	int currentOption; // e.g. different type of mustache
	int currentColor; //0:black, 1: red, 2:blue, 3:green, 4: yellow, 5:purple
};

