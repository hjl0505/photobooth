// Hat.cpp
// Chris Knakal and Hyungjin Lee
// CSS 487 Program 4 -- Photobooth
// 11.19.2016
//
// Draws a hat on the input image

#include "Hat.h"
#include <cmath>

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
	Mat tempHat5 = imread("pictures/hat5.jpg", IMREAD_GRAYSCALE);
	
	// convert into B/W color image, save into hats array
	convertBW(tempHat1, hats[0]);
	convertBW(tempHat2, hats[1]);
	convertBW(tempHat3, hats[2]);
	convertBW(tempHat4, hats[3]);
	convertBW(tempHat5, hats[4]);
}

// putHat
// Displays at in the image at the current 
// pre: image is valid. x and y position is within the image, and valid color[]
// post: image contains a hat on top of the detected head with given color
void Hat::putHat(Mat& image, int x, int y, int colors[]) {
	for (int r = 0; r < hats[currentHatIdx].rows; r++) {
		for (int c = 0; c < hats[currentHatIdx].cols; c++) {
			// get values from curent hat image
			int tempBlue = hats[currentHatIdx].at<Vec3b>(r, c)[0];
			int tempGreen = hats[currentHatIdx].at<Vec3b>(r, c)[1];
			int tempRed = hats[currentHatIdx].at<Vec3b>(r, c)[2];

			// check if color is black and write over the image
			if (tempBlue < 255 && tempGreen < 255 && tempRed < 255) {
				// Adjust position to where face is in the image
				int tempRow = y - hats[currentHatIdx].rows + r; 
				int tempCol = x + c; //<------------------------------------- NEED TO ADJUST (maybe?)

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
