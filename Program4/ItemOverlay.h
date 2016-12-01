#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "Hat.h"
#include "Glasses.h"
#include "Mustache.h"

using namespace cv;
using namespace std;

#pragma once

class ItemOverlay
{
public:
	ItemOverlay();

	void putHat(Mat& image, vector<Rect_<int>> faces);
	void putGlasses(Mat& image, vector<Rect_<int>> eyes);
	void putMustache(Mat& image, vector<Rect_<int>> mouths, vector<Rect_<int>> noses);

	void nextColor();
	void lastColor();
	void nextOption();
	void lastOption();


private:
	const int COLOR_COUNT = 8;
	const int MAX_FRAME = 10;
	
	int colorChart[3] = { 0, 0, 0 }; // 0: blue, 1: green, 2: red
	char currentItem; // 1: hat, 2: glasses, 3: mustache
	int currentOption; // e.g. different type of mustache
	int currentColor; //0:black, 1: red, 2:blue, 3:green, 4: yellow, 5:Orange
	int lastX;
	int lastY;
	int frameCount;

	Hat hatter;
	Glasses glasses;
	Mustache mustache;

	void setColorChart();
	bool checkFrame();
};

