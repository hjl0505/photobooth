#include "Pixelate.h"



Pixelate::Pixelate()
{
	divisions = 80;
}

void Pixelate::pixelator(Mat& image, Rect face) {

	int blockWidth = image.cols / divisions;
	int blockHeight = image.rows / divisions;

	for (int r = 0; r < face.height; r += blockHeight) {
		for (int c = 0; c < face.width; c+= blockWidth) {

			int blue, green, red;
			getAvgBlockColor(image, face, r, c, blue, green, red);

			Point upperLeft(c + face.x, r + face.y);
			Point lowerRight(c + face.x + blockWidth, r + face.y + blockHeight);

			if (lowerRight.x < image.cols && lowerRight.y < image.rows) {
				rectangle(image, upperLeft, lowerRight, Scalar(blue, green, red), -1, 8);
			}
		}
	}
}

void Pixelate::getAvgBlockColor(Mat& image, Rect face, int row, int col, int& blue, int& green, int& red) {
	int blockWidth = image.cols / divisions;
	int blockHeight = image.rows / divisions;

	int blueTot = 0;
	int greenTot = 0;
	int redTot = 0;
	int pixelTot = blockWidth * blockHeight;

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

	blue = blueTot / pixelTot;
	green = greenTot / pixelTot;
	red = redTot / pixelTot;
}

void Pixelate::nextOption() {
	divisions += 10;
	if (divisions > 100) {
		divisions = 20;
	}
}

void Pixelate::lastOption() {
	divisions -= 10;
	if (divisions <= 10) {
		divisions = 100 - divisions;
	}
}
