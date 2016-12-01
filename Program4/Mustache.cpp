// Mustache.cpp
// Chris Knakal and Hyungjin Lee
// CSS 487 Program 4 -- Photobooth
// 11.19.2016
//
// Draws a pair of mustache on the input image

#include "Mustache.h"

// Constructor
// Initializes an array of mustaches
Mustache::Mustache() {

	// Start with mustache 1, index 0
	currentMustacheIndex = 0;

	// Read mustaches images as grayscale
	Mat tempMustache1 = imread("pictures/mustache1.jpg", IMREAD_GRAYSCALE);
	Mat tempMustache2 = imread("pictures/mustache2.jpg", IMREAD_GRAYSCALE);
	Mat tempMustache3 = imread("pictures/mustache3.jpg", IMREAD_GRAYSCALE);
	Mat tempMustache4 = imread("pictures/mustache4.jpg", IMREAD_GRAYSCALE);
	Mat tempMustache5 = imread("pictures/mustache5.jpg", IMREAD_GRAYSCALE);
	Mat tempMustache6 = imread("pictures/mustache6.jpg", IMREAD_GRAYSCALE);
	Mat tempMustache7 = imread("pictures/mustache7.jpg", IMREAD_GRAYSCALE);

	// convert into B/W color image, save into mustaches array
	convertBW(tempMustache1, mustache[0]);
	convertBW(tempMustache2, mustache[1]);
	convertBW(tempMustache3, mustache[2]);
	convertBW(tempMustache4, mustache[3]);
	convertBW(tempMustache5, mustache[4]);
	convertBW(tempMustache6, mustache[5]);
	convertBW(tempMustache7, mustache[6]);
}

// putMustache
// Displays at in the image at the current 
// pre: image is valid. x and y position is within the image, and valid color[]
// post: image contains a pair of Mustache on top of the detected head with given color
void Mustache::putMustache(Mat& image, int x, int y, int colors[]) {
	for (int r = 0; r < currentScaledMustache.rows; r++) {
		for (int c = 0; c < currentScaledMustache.cols; c++) {
			// get values from curent mustache image
			int tempBlue = currentScaledMustache.at<Vec3b>(r, c)[0];
			int tempGreen = currentScaledMustache.at<Vec3b>(r, c)[1];
			int tempRed = currentScaledMustache.at<Vec3b>(r, c)[2];

			// check if color is black and write over the image
			if (tempBlue < 255 && tempGreen < 255 && tempRed < 255) {
				// Adjust position to where mouth is in the image
				// between mouth and nose
				int tempRow = y + r -(currentScaledMustache.rows / 8);
				int tempCol = x + c - (currentScaledMustache.cols / 8);

				// Ignore if mustache position goes out of bounds of the image
				if (tempRow < image.rows && tempCol < image.cols && tempRow >= 0 && tempCol >= 0) {
					image.at<Vec3b>(tempRow, tempCol)[0] = colors[0];
					image.at<Vec3b>(tempRow, tempCol)[1] = colors[1];
					image.at<Vec3b>(tempRow, tempCol)[2] = colors[2];
				}
			}
		}
	}
}

// convertBW
// converts grey image of the Mustache into black and white color image 
// pre: images are valid
// post: binary image of a pair of Mustache is converted to color image format
void Mustache::convertBW(Mat& binaryMustache, Mat& colorMustache) {

	// make grey image into binary black and white image
	threshold(binaryMustache, binaryMustache, 128, 255, THRESH_BINARY);
	Mat newMustache(binaryMustache.rows, binaryMustache.cols, CV_8UC3, Scalar(0, 0, 0));

	// Copy over binary image to color format
	for (int r = 0; r < newMustache.rows; r++) {
		for (int c = 0; c < newMustache.cols; c++) {
			int tempBw = binaryMustache.at<uchar>(r, c);
			if (tempBw == 255) {
				newMustache.at<Vec3b>(r, c)[0] = 255;
				newMustache.at<Vec3b>(r, c)[1] = 255;
				newMustache.at<Vec3b>(r, c)[2] = 255;
			}
		}
	}

	// Copy the new color mustache over to colorMustache in the mustache array
	colorMustache = newMustache.clone();
}

// scaleMustache
// currently selected mustache will be scaled to fit the mouth 
// pre: width and height of a face are valid
// post: Mustache image will be scaled to dimensions of width and height
void Mustache::scaleMustache(int width, int height) {
	Size faceSize(static_cast<int>(width * 1.35), static_cast<int>(height * 2));
	// scale a fresh copy of Mustache at currentMustacheIndex
	resize(mustache[currentMustacheIndex], currentScaledMustache, faceSize);
}

// nextOption
// get next index in the circular mustache array
// pre: none
// post: currentMustacheIndex incremented by 1
void Mustache::nextOption() {
	currentMustacheIndex = (currentMustacheIndex + 1) % MUSTACHE_COUNT;
}

// lastOption
// get previous index in the circular mustache array
// pre: none
// post: currentMustacheIndex decremented by 1
void Mustache::lastOption() {
	currentMustacheIndex = (MUSTACHE_COUNT + (currentMustacheIndex - 1)) % MUSTACHE_COUNT;
}