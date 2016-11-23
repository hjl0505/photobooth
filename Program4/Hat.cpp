#include "Hat.h"



Hat::Hat()
{
	currentHat = 1;
	Mat tempHat1 = imread("pictures/hat1.jpg", IMREAD_GRAYSCALE);
	Mat tempHat2 = imread("pictures/hat2.jpg", IMREAD_GRAYSCALE);

	convertBW(tempHat1, hat1);
	//convertBW(tempHat2, hat2);
}

void Hat::putHat(Mat& image, int x, int y) {
	for (int r = 0; r < hat1.rows; r++) {
		for (int c = 0; c < hat1.cols; c++) {
			int tempBlue = hat1.at<Vec3b>(r, c)[0];
			int tempGreen = hat1.at<Vec3b>(r, c)[1];
			int tempRed = hat1.at<Vec3b>(r, c)[2];

			if (tempBlue < 255 && tempGreen < 255 && tempRed < 255) {
				int tempRow = r + y;
				int tempCol = c + x;

				if (tempRow < image.rows && tempCol < image.cols && tempRow >= 0 && tempCol >= 0) {
					image.at<Vec3b>(tempRow, tempCol)[0] = 0;
					image.at<Vec3b>(tempRow, tempCol)[1] = 0;
					image.at<Vec3b>(tempRow, tempCol)[2] = 0;
				}
			}
		}
	}		
}

void Hat::convertBW(Mat& binaryHat, Mat& colorHat) {
	threshold(binaryHat, binaryHat, 128, 255, THRESH_BINARY);
	Mat newHat(binaryHat.rows, binaryHat.cols, CV_8UC3, Scalar(0, 0, 0));

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

	colorHat = newHat.clone();
}
