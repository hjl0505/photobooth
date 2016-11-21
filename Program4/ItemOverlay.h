#include "FaceRecognition.h"

#pragma once
class ItemOverlay
{
public:
	ItemOverlay();
	~ItemOverlay();

	void putHat(Mat& image, vector<Rect_<int>> faces);
	void nextColor();
	void nextOption();


private:
	FaceRecognition FR; // FaceRecognition class
	int currentOption; // e.g. different type of mustache
	int currentColor; //0:black, 1: red, 2:blue, 3:green, 4: yellow, 5:purple
};

