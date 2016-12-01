#include "Pixelate.h"



Pixelate::Pixelate()
{
}

void Pixelate::pixelator(Mat& image, Rect face) {

	int blockWidth = image.cols / 40;
	int blockHeight = image.rows / 40;
	int pixelTot = blockWidth * blockHeight;

	for (int r = 0; r < face.height; r += blockHeight) {
		for (int c = 0; c < face.width; c+= blockWidth) {
			int blueTot = 0;
			int greenTot = 0;
			int redTot = 0;

			for (int pixelX = 0; pixelX < blockWidth; pixelX++) {
				for (int pixelY = 0; pixelY < blockHeight; pixelY++) {
					blueTot += image.at<Vec3b>(r + face.height + pixelY, c + pixelX + face.width)[0];
					greenTot += image.at<Vec3b>(r + face.height + pixelY, c + pixelX + face.width)[1];
					redTot += image.at<Vec3b>(r + face.height + pixelY, c + pixelX + face.width)[2];
				}
			}
			

			int blue = blueTot / pixelTot;
			int green = greenTot / pixelTot;
			int red = redTot / pixelTot;

			rectangle(image, Point(c + face.x, r + face.y), Point(c + face.x + blockWidth, r + face.y + blockHeight), Scalar(blue, green, red), -1, 8);
		}
	}
}
