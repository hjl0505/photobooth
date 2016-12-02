// Glasses.cpp
// Chris Knakal and Hyungjin Lee
// CSS 487 Program 4 -- Photobooth
// 11.19.2016
//
// Draws a pair of glasses on the input image

#include "Glasses.h"

// Constructor
// Initializes an array of glasses with glasses
Glasses::Glasses() {

	// Start with glasses 1, index 0
	currentGlassesIndex = 0;

	// Read glasses images as grayscale
	Mat tempGlasses1 = imread("pictures/glasses1.jpg", IMREAD_GRAYSCALE);
	Mat tempGlasses2 = imread("pictures/glasses2.jpg", IMREAD_GRAYSCALE);
	Mat tempGlasses3 = imread("pictures/glasses3.jpg", IMREAD_GRAYSCALE);

	// convert into B/W color image, save into glasses array
	convertBW(tempGlasses1, glasses[0]);
	convertBW(tempGlasses2, glasses[1]);
	convertBW(tempGlasses3, glasses[2]);
}

// putGlasses
// Displays colored glass in the image at the current detected left eye
// pre: image is valid. x and y position is within the image, and valid color[]
// post: image contains a pair of glasses on top of the detected head with given color
void Glasses::putGlasses(Mat& image, int x, int y, int colors[]) {
	for (int r = 0; r < currentScaledGlasses.rows; r++) {
		for (int c = 0; c < currentScaledGlasses.cols; c++) {
			// get values from curent glasses image
			int tempBlue = currentScaledGlasses.at<Vec3b>(r, c)[0];
			int tempGreen = currentScaledGlasses.at<Vec3b>(r, c)[1];
			int tempRed = currentScaledGlasses.at<Vec3b>(r, c)[2];

			// check if color is black and write over the image
			if (tempBlue < 255 && tempGreen < 255 && tempRed < 255) {
				// Adjust position to where eyes are in the image
				// starts from upper left corner of left eye
				int tempRow = y + r - (currentScaledGlasses.rows / 7);
				int tempCol = x + c - (currentScaledGlasses.cols / 10);

				// Ignore if glasses position goes out of bounds of the image
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
// converts grey image of the glasses into black and white color image
// pre: images are valid
// post: binary image of a pair of glasses is converted to color image format
void Glasses::convertBW(Mat& binaryGlasses, Mat& colorGlasses) {

	// make grey image into binary black and white image
	threshold(binaryGlasses, binaryGlasses, 128, 255, THRESH_BINARY);
	Mat newGlasses(binaryGlasses.rows, binaryGlasses.cols, CV_8UC3, Scalar(0, 0, 0));

	// Copy over binary image to color format
	for (int r = 0; r < newGlasses.rows; r++) {
		for (int c = 0; c < newGlasses.cols; c++) {
			int tempBw = binaryGlasses.at<uchar>(r, c);
			if (tempBw == 255) {
				newGlasses.at<Vec3b>(r, c)[0] = 255;
				newGlasses.at<Vec3b>(r, c)[1] = 255;
				newGlasses.at<Vec3b>(r, c)[2] = 255;
			}
		}
	}

	// Copy the new color hat over to colorHat in the hat array
	colorGlasses = newGlasses.clone();
}

// scaleGlasses
// currently selected glasses will be scaled to fit the eyes
// pre: width and height of a face are valid
// post: glasses image will be scaled to dimensions of width and height
void Glasses::scaleGlasses(int width, int height) {
	Size faceSize(static_cast<int>(width * 4), static_cast<int>(height * 1.5));
	// scale a fresh copy of glasses at currentGlassesIndex
	resize(glasses[currentGlassesIndex], currentScaledGlasses, faceSize);
}

// nextOption
// get next index in the circular glasses array
// pre: none
// post: currentGlassesIndex incremented by 1
void Glasses::nextOption() {
	currentGlassesIndex = (currentGlassesIndex + 1) % GLASSES_COUNT;
}

// lastOption
// get previous index in the circular glasses array
// pre: none
// post: currentGlassesIndex decremented by 1
void Glasses::lastOption() {
	currentGlassesIndex = (GLASSES_COUNT + (currentGlassesIndex - 1)) % GLASSES_COUNT;
}
