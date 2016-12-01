// ItemOverlay.h
// Chris Knakal and Hyungjin Lee
// CSS 487 Program 4 -- Photobooth
// 11.19.2016
//
// Overlays a Hat, Glasses, or Mustache onto the image

#include <opencv2/highgui/highgui.hpp>
#include "Hat.h"
#include "Glasses.h"
#include "Mustache.h"

using namespace cv;
using namespace std;

#pragma once

class ItemOverlay
{
public:
	// Constructor
	ItemOverlay();

	// Functions
	void putHat(Mat& image, vector<Rect_<int>> faces);
	void putGlasses(Mat& image, vector<Rect_<int>> eyes);
	void putMustache(Mat& image, vector<Rect_<int>> mouths, vector<Rect_<int>> noses);
	void nextColor();
	void lastColor();
	void nextOption();
	void lastOption();


private:
	// Helper Functions
	void setColorChart();
	bool checkFrame();

	// Variables
	const int COLOR_COUNT = 8; 
	const int MAX_FRAME = 10; // number of skip frames
	
	int colorChart[3] = { 0, 0, 0 }; // 0: blue, 1: green, 2: red
	char currentItem; // 1: hat, 2: glasses, 3: mustache
	int currentOption; // e.g. different type of mustache
	int currentColor; //0:black, 1: red, 2:blue, 3:green, 4: yellow, 5:Orange

	// Used to smooth out the item drawing by skipping frames
	int lastX; 
	int lastY;
	int frameCount;

	Hat hatter;
	Glasses glasses;
	Mustache mustache;
};

