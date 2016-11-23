#include "ItemOverlay.h"

ItemOverlay::ItemOverlay()
{
	currentItem = '0'; // default = No item
	//colorchart[COLOR_COUNT][3]; // [Color][0] : blue, [Color][1] : green, [Color][2] : red
}

void ItemOverlay::putHat(Mat& image, vector<Rect_<int>> faces) {
	currentItem = '1';

	for (int i = 0; i < faces.size(); i++) {
		Rect face = faces[i];
		hatter.putHat(image, face.x, face.y, colorchart[currentColor]); // <----------------- might need to adjust this??
	}
}

void ItemOverlay::putGlasses(Mat& image, vector<Rect_<int>> faces) {
	currentItem = '2';
}

void ItemOverlay::putMustache(Mat& image, vector<Rect_<int>> faces) {
	currentItem = '3';
}

void ItemOverlay::nextColor(Mat& image) {
	currentColor = (currentColor + 1) % COLOR_COUNT;
}
void ItemOverlay::lastColor(Mat& image) {
	currentColor = (currentColor - 1) % COLOR_COUNT;
}
void ItemOverlay::nextOption(Mat& image) {

}
void ItemOverlay::lastOption(Mat& image) {

}