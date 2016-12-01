// Pixelate.cpp
// Chris Knakal and Hyungjin Lee
// CSS 487 Program 4 -- Photobooth
// 11.19.2016
//
// Pixelates Faces by varying degrees

#include "Pixelate.h"

// Constructor
// Initializes variables
Pixelate::Pixelate()
{
	// default
	divisions = 40;
}

// pixelateFace
// pixelates face
// pre: valid input image
// post: the face in the image is pixelated
void Pixelate::pixelateFace(Mat& image, Rect face) {

	// get pixelated block width and height
	int blockWidth = image.cols / divisions;
	int blockHeight = image.rows / divisions;

	for (int r = 0; r < face.height; r += blockHeight) {
		for (int c = 0; c < face.width; c+= blockWidth) {

			// calculate average blue, green, red for the block
			int blue, green, red;
			getAvgBlockColor(image, face, r, c, blue, green, red);

			// get upper left and lower right points of the block
			Point upperLeft(c + face.x, r + face.y);
			Point lowerRight(c + face.x + blockWidth, r + face.y + blockHeight);

			// if the points are within image bounds, draw a rectange with average colors
			if (lowerRight.x < image.cols && lowerRight.y < image.rows) {
				rectangle(image, upperLeft, lowerRight, Scalar(blue, green, red), -1, 8);
			}
		}
	}
}

// getAvgBlockColor
// calculates average blue, green, red of the pixelated block
// pre: valid input image
// post: average blue, green, red calculated
void Pixelate::getAvgBlockColor(Mat& image, Rect face, int row, int col, int& blue, int& green, int& red) {
	int blockWidth = image.cols / divisions;
	int blockHeight = image.rows / divisions;

	int blueTot = 0;
	int greenTot = 0;
	int redTot = 0;
	int pixelTot = blockWidth * blockHeight;


	// sum up all the blue, green, red values in the block
	for (int pixelRow = 0; pixelRow < blockWidth; pixelRow++) {
		for (int pixelCol = 0; pixelCol < blockHeight; pixelCol++) {
			Point pixel((col + pixelCol + face.x), (row + pixelRow + face.y));

			if (pixel.x <= image.cols && pixel.y <= image.rows) {
				blueTot += image.at<Vec3b>(pixel.y, pixel.x)[0];
				greenTot += image.at<Vec3b>(pixel.y, pixel.x)[1];
				redTot += image.at<Vec3b>(pixel.y, pixel.x)[2];
			}
		}
	}

	// calculate average
	blue = blueTot / pixelTot;
	green = greenTot / pixelTot;
	red = redTot / pixelTot;
}

// nextOption
// increment divisions by 10, range is 10 - 90
// pre: none
// post: division is incremented by 10, or starts again at 10
void Pixelate::nextOption() {
	divisions += 10;
	if (divisions > 100) {
		divisions = 20;
	}
}

// lastOption
// decrement divisions by 10, range is 10 - 90
// pre: none
// post: division is decremented by 10, or starts again at 90
void Pixelate::lastOption() {
	divisions -= 10;
	if (divisions <= 10) {
		divisions = 100 - divisions;
	}
}
