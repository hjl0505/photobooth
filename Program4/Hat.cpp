// Hat.cpp
// Chris Knakal and Hyungjin Lee
// CSS 487 Program 4 -- Photobooth
// 11.19.2016
//
// Draws a hat on the input image

#include "Hat.h"

// Constructor
// Initializes array of hats with hats
Hat::Hat()
{
	// Start with hat 1, index 0
	currentHatIdx = 0;
	
	// Read hat images as grayscale
	Mat tempHat1 = imread("pictures/hat1.jpg", IMREAD_GRAYSCALE);
	Mat tempHat2 = imread("pictures/hat2.jpg", IMREAD_GRAYSCALE);
	Mat tempHat3 = imread("pictures/hat3.jpg", IMREAD_GRAYSCALE);
	Mat tempHat4 = imread("pictures/hat4.jpg", IMREAD_GRAYSCALE);
	
	// convert into B/W color image, save into hats array
	convertBW(tempHat1, hats[0]);
	convertBW(tempHat2, hats[1]);
	convertBW(tempHat3, hats[2]);
	convertBW(tempHat4, hats[3]);

}

// putHat
// Displays at in the image at the current 
// pre: image is valid. x and y position is within the image, and valid color[]
// post: image contains a hat on top of the detected head with given color
void Hat::putHat(Mat& image, int x, int y, int colors[]) {
	for (int r = 0; r < currentScaledHat.rows; r++) {
		for (int c = 0; c < currentScaledHat.cols; c++) {
			// get values from curent hat image
			int tempBlue = currentScaledHat.at<Vec3b>(r, c)[0];
			int tempGreen = currentScaledHat.at<Vec3b>(r, c)[1];
			int tempRed = currentScaledHat.at<Vec3b>(r, c)[2];

			// check if color is black and write over the image
			if (tempBlue < 255 && tempGreen < 255 && tempRed < 255) {
				// Adjust position to where face is in the image
				// on top of the head
				int tempRow = y - currentScaledHat.rows + r + (currentScaledHat.rows / 10);
				int tempCol = x + c;

				// Ignore if hat position goes out of bounds of the image
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
// converts grey image of the hat into black and white color image 
// pre: images are valid
// post: binary image of a hat is converted to color image format
void Hat::convertBW(Mat& binaryHat, Mat& colorHat) {
	
	// make grey image into binary black and white image
	threshold(binaryHat, binaryHat, 128, 255, THRESH_BINARY);
	Mat newHat(binaryHat.rows, binaryHat.cols, CV_8UC3, Scalar(0, 0, 0));

	// Copy over binary image to color format
	for (int r = 0; r < newHat.rows; r++) {
		for (int c = 0; c < newHat.cols; c++) {
			int tempBw = binaryHat.at<uchar>(r, c);
			if (tempBw == 255) {
				newHat.at<Vec3b>(r, c)[0] = 255;
				newHat.at<Vec3b>(r, c)[1] = 255;
				newHat.at<Vec3b>(r, c)[2] = 255;
			}
		}
	}

	// Copy the new color hat over to colorHat in the hat array
	colorHat = newHat.clone();
}

// scaleHat
// currently selected hat will be scaled to fit the face
// pre: width and height of a face are valid
// post: hat image will be scaled to dimensions of width and height
void Hat::scaleHat(int width, int height) {
	Size faceSize(width, height);
	resize(hats[currentHatIdx], currentScaledHat, faceSize);
}

// nextOption
// get next index in the circular hat array
// pre: none
// post: currentHatIdx incremented by 1
void Hat::nextOption() {
	currentHatIdx = (currentHatIdx + 1) % HAT_COUNT;
}

// lastOption
// get previous index in the circular hat array
// pre: none
// post: currentHatIdx decremented by 1
void Hat::lastOption() {
	currentHatIdx = (HAT_COUNT + (currentHatIdx - 1)) % HAT_COUNT;
}