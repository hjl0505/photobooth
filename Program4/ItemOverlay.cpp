// ItemOverlay.cpp
// Chris Knakal and Hyungjin Lee
// CSS 487 Program 4 -- Photobooth
// 11.19.2016
//
// Overlays a Hat, Glasses, or Mustache onto the image

#include "ItemOverlay.h"

// Constructor
// Initializes variables
ItemOverlay::ItemOverlay()
{
	currentItem = '0'; // default = No item
	currentColor = 0; // current color is black

	// Used to smooth out the item drawing by skipping frames
	lastX = -1; 
	lastY = -1;
	frameCount = 0;
}

// putHat
// draws hat on top of all the faces
// pre: images are valid
// post: every detected face in the image has a hat on
void ItemOverlay::putHat(Mat& image, vector<Rect_<int>> faces) {
	currentItem = '1';

	for (int i = 0; i < faces.size(); i++) {
		// resize hat
		Rect face = faces[i];
		hatter.scaleHat(face.width, face.height);

		// draw hat
		hatter.putHat(image, face.x, face.y, colorChart);
	}
}

// putGlasses
// draws glasses on all pairs of eyes
// pre: images are valid
// post: every detected pair of eyes in the image has glasses on
void ItemOverlay::putGlasses(Mat& image, vector<Rect_<int>> eyes) {
	currentItem = '2';

	// Check if pair of eyes are detected
	for (int i = 0; i < eyes.size(); i += 2) {
		if ((i + 1) < eyes.size()) {
			Rect rightEye = eyes[i];
			Rect leftEye = eyes[i + 1];

			// determine which eye is the left eye
			if (leftEye.x > rightEye.x) {
				leftEye = rightEye;
			}

			// use left eye to sclae and position the glasses
			glasses.scaleGlasses(leftEye.width, leftEye.height);
			glasses.putGlasses(image, leftEye.x, leftEye.y, colorChart);
		}
	}
}

// putMustache
// draws mustaches between mouth and nose
// pre: images are valid
// post: every detected pair of eyes in the image has glasses on
void ItemOverlay::putMustache(Mat& image, vector<Rect_<int>> mouths, vector<Rect_<int>> noses) {
	currentItem = '3';

	// check for mouths under noses
	vector<Rect_<int>> tempMouths;
	for (int m = 0; m < mouths.size(); m++) {
		for (int n = 0; n < noses.size(); n++) {
			Rect mouth = mouths[m];
			Rect nose = noses[n];

			// add the mouth into tempMouth list
			if ((nose.y + nose.height) <= (mouth.y)) {
				tempMouths.push_back(mouth);
				break;
			}
		}
	}

	// draw mustache on all mouths that are under a nose
	for (int i = 0; i < tempMouths.size(); i++)
	{
		Rect mouth = tempMouths[i];
		mustache.scaleMustache(mouth.width, mouth.height);
		mustache.putMustache(image, mouth.x, mouth.y, colorChart);
	}
}

// nextColor
// increment current color by 1, or start again from 0
// pre: none
// post: current color incremented, and colorchart reset to new color 
void ItemOverlay::nextColor() {
	currentColor = (currentColor + 1) % COLOR_COUNT;
	setColorChart();
}

// lastColor
// decrement current color by 1, or start again from COLOR_COUNT - 1
// pre: none
// post: current color decremented, and colorchart reset to new color 
void ItemOverlay::lastColor() {
	currentColor = (COLOR_COUNT + (currentColor - 1)) % COLOR_COUNT;
	setColorChart();
}

// setColorChart
// reset the color chart with currentColor key
// pre: none
// post: color chart contains values of indicated color as BGR
void ItemOverlay::setColorChart() {
	switch (currentColor) {
		case 0: // Black
			colorChart[0] = 0;
			colorChart[1] = 0;
			colorChart[2] = 0;
			break;
		case 1: // Red
			colorChart[0] = 0;
			colorChart[1] = 0;
			colorChart[2] = 255;
			break;
		case 2: // Blue
			colorChart[0] = 255;
			colorChart[1] = 0;
			colorChart[2] = 0;
			break;
		case 3: // Green
			colorChart[0] = 0;
			colorChart[1] = 255;
			colorChart[2] = 0;
			break;
		case 4: // Yellow
			colorChart[0] = 0;
			colorChart[1] = 255;
			colorChart[2] = 255;
			break;
		case 5: // Orange
			colorChart[0] = 0;
			colorChart[1] = 125;
			colorChart[2] = 255;
			break;
		case 6: // Cyan
			colorChart[0] = 255;
			colorChart[1] = 2555;
			colorChart[2] = 0;
			break;
		case 7: // Magenta
			colorChart[0] = 255;
			colorChart[1] = 0;
			colorChart[2] = 255;
			break;
		default:
			break; // Did not match any of the current colors
				   // Do nothing
	}
}

// nextOption
// calls the appropriate nextOption function depending on the currentItem selected
// pre: none
// post: next option of currentItem is called
void ItemOverlay::nextOption() {
	switch (currentItem) {
	case '1': // hat
		hatter.nextOption();
		break;
	case '2': // glasses
		glasses.nextOption();
		break;
	case '3': // mustache
		mustache.nextOption();
		break;
	default:
		break;
	}
}

// lastOption
// calls the appropriate lastOption function depending on the currentItem selected
// pre: none
// post: last option of currentItem is called
void ItemOverlay::lastOption() {
	switch (currentItem) {
	case '1': // hat
		hatter.lastOption();
		break;
	case '2': // glasses
		glasses.lastOption();
		break;
	case '3': // mustache
		mustache.lastOption();
		break;
	default:
		break;
	}
}

// checkFrame
// increment frame and check if frame should be skipped
// pre: none
// post: returns true if frame is good to be drawn a new item, or false if it should be skipped
bool ItemOverlay::checkFrame() {
	frameCount++;
	if (lastX == -1 && lastY == -1) {
		return true;
	}
	if (frameCount == MAX_FRAME) {
		frameCount = 0;
		return true;
	}
	return false;
}