#include "ItemOverlay.h"

ItemOverlay::ItemOverlay()
{
	currentItem = '0'; // default = No item
	currentColor = 0;
	//colorChart[COLOR_COUNT][3]; // [Color][0] : blue, [Color][1] : green, [Color][2] : red
}

void ItemOverlay::putHat(Mat& image, vector<Rect_<int>> faces) {
	currentItem = '1';

	for (int i = 0; i < faces.size(); i++) {
		Rect face = faces[i];
		hatter.scaleHat(face.width, face.height);
		hatter.putHat(image, face.x, face.y, colorChart);
	}
}

void ItemOverlay::putGlasses(Mat& image, vector<Rect_<int>> faces) {
	currentItem = '2';

	for (int i = 0; i < faces.size(); i += 2) {
		Rect face = faces[i];
		glasses.scaleGlasses(face.width, face.height);
		glasses.putGlasses(image, face.x, face.y, colorChart);
	}
}

void ItemOverlay::putMustache(Mat& image, vector<Rect_<int>> faces) {
	currentItem = '3';

	for (int i = 0; i < faces.size(); i++)
	{
		Rect face = faces[i];
		mustache.scaleMustache(face.width, face.height);
		mustache.putMustache(image, face.x, face.y, colorChart);
	}
}

void ItemOverlay::nextColor() {
	currentColor = (currentColor + 1) % COLOR_COUNT;
	setColorChart();
}

void ItemOverlay::lastColor() {
	currentColor = (COLOR_COUNT + (currentColor - 1)) % COLOR_COUNT;
	setColorChart();
}

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
			break; // Did not match any of the current keys
				   // Do nothing
	}
}

void ItemOverlay::nextOption() {
	switch (currentItem) {
	case '1': // hat
		hatter.nextOption();
		break;
	case '2': // glasses
		glasses.nextOption();
		break;
	case '3': // mustache
		break;
	default:
		break;
	}
}
void ItemOverlay::lastOption() {
	switch (currentItem) {
	case '1': // hat
		hatter.lastOption();
		break;
	case '2': // glasses
		glasses.lastOption();
		break;
	case '3': // mustache
		break;
	default:
		break;
	}
}