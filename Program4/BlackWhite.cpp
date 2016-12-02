// BlackWhite.cpp
// Chris Knakal and Hyungjin Lee
// CSS 487 Program 4 -- Photobooth
// 11.19.2016
//
// Converts image into greyscale image, except for selected color (black, red, blue, green)
// If color Black is selected, it shows regular greyscale image.
#include "BlackWhite.h"

// Constructor
// Initializes variables
BlackWhite::BlackWhite() {
	currentColor = 0;
}

// makeBW
// Selects color by using HSV from the image, and converts rest of the image into greyscale
// pre: image is in BGR format
// post: greyscaled image returned in BGR format
void BlackWhite::makeBW(Mat& image) {
	//Convert the image from BGR to HSV
	Mat imgHSV;
	cvtColor(image, imgHSV, COLOR_BGR2HSV);

	// Threshold the HSV image for the selected color
	// White indicate the color is detected, black otherwise
	Mat thresholdImg;
	thresholdImage(imgHSV, thresholdImg);

	// Convert to greyscale using average value for pixels without the selected pixel
	for (int r = 0; r < image.rows; r++) {
		for (int c = 0; c < image.cols; c++) {
			int threshold = thresholdImg.at<uchar>(r, c);

			// check if threshold is black
			if (threshold == 0) {

				// calculate average
				int blue = image.at<Vec3b>(r, c)[0];
				int green = image.at<Vec3b>(r, c)[1];
				int red = image.at<Vec3b>(r, c)[2];
				int total = blue + green + red;

				// convert into greyscale
				image.at<Vec3b>(r, c)[0] = total / 3;
				image.at<Vec3b>(r, c)[1] = total / 3;
				image.at<Vec3b>(r, c)[2] = total / 3;
			}
		}
	}
}

// thresholdImage
// Creates a threshold image of the current color selected using HSV
// The threshold is dependent on the lighting and the surface of the object
// pre: image is in HSV format
// post: threshold image contains white to indicate the color detected, black otherwise
void BlackWhite::thresholdImage(Mat& imgHSV, Mat& image) {
	switch (currentColor) {
		case 0: // black
			inRange(imgHSV, Scalar(0, 255, 255), Scalar(0, 255, 255), image);
			break;
		case 1: // red
			inRange(imgHSV, Scalar(120, 150, 60), Scalar(179, 255, 255), image);
			break;
		case 2: // blue
			inRange(imgHSV, Scalar(95, 150, 60), Scalar(130, 255, 255), image);
			break;
		case 3: // green
			inRange(imgHSV, Scalar(35, 110, 85), Scalar(105, 175, 225), image);
			break;
	}
}

// nextColor
// selects the next color in the current rotation of thresholds
// pre: none
// post: next color in the rotation of threshold is selected as current
void BlackWhite::nextColor() {
	currentColor = (currentColor + 1) % COLOR_COUNT;
}

// lastColor
// selects the previous color in the current rotation of thresholds
// pre: none
// post: previous color in the rotation of threshold is selected as current
void BlackWhite::lastColor() {
	currentColor = (COLOR_COUNT + currentColor - 1) % COLOR_COUNT;
}
