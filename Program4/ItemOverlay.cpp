#include "ItemOverlay.h"

ItemOverlay::ItemOverlay()
{
	currentItem = '0'; // default = No item
	currentColor = 0;
}

void ItemOverlay::putHat(Mat& image, vector<Rect_<int>> faces) {
	currentItem = '1';

	for (int i = 0; i < faces.size(); i++) {
		Rect face = faces[i];
		hatter.scaleHat(face.width, face.height);
		hatter.putHat(image, face.x, face.y, colorChart);
	}
}

void ItemOverlay::putGlasses(Mat& image, vector<Rect_<int>> eyes) {
	currentItem = '2';

	// Check if pair of eyes are detected
	for (int i = 0; i < eyes.size(); i += 2) {
		Rect rightEye = eyes[i];
		if ((i + 1) < eyes.size()) {
			Rect leftEye = eyes[i + 1];

			if (leftEye.x > rightEye.x) {
				glasses.scaleGlasses(rightEye.width, rightEye.height);
				glasses.putGlasses(image, rightEye.x, rightEye.y, colorChart);
			}
		}
	}
}

void ItemOverlay::putMustache(Mat& image, vector<Rect_<int>> mouths, vector<Rect_<int>> noses) {
	currentItem = '3';

	// check for mouths under noses
	vector<Rect_<int>> tempMouths;
	for (int m = 0; m < mouths.size(); m++) {
		for (int n = 0; n < noses.size(); n++) {
			Rect mouth = mouths[m];
			Rect nose = noses[n];

			if ((nose.y + nose.height / 2) <= (mouth.y + mouth.height / 2)) {
				tempMouths.push_back(mouth);
				break;
			}
		}
	}

	for (int i = 0; i < tempMouths.size(); i++)
	{
		Rect mouth = tempMouths[i];
		mustache.scaleMustache(mouth.width, mouth.height);
		mustache.putMustache(image, mouth.x, mouth.y, colorChart);
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
		mustache.nextOption();
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
		mustache.lastOption();
		break;
	default:
		break;
	}
}