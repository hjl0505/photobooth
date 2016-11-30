#include "BlackWhite.h"

BlackWhite::BlackWhite() {
	currentColor = 0;
}

void BlackWhite::makeBW(Mat& image) {
	//Convert the captured frame from BGR to HSV
	Mat imgHSV;
	cvtColor(image, imgHSV, COLOR_BGR2HSV);

	Mat imgThresholded;
	thresholdImage(imgHSV, imgThresholded);

	//morphological opening (remove small objects from the foreground)
	erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

	//morphological closing (fill small holes in the foreground)
	dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

	// Convert to AVG greyscale if color not detected
	for (int r = 0; r < image.rows; r++) {
		for (int c = 0; c < image.cols; c++) {
			int i = imgThresholded.at<uchar>(r, c);
			if (i == 0) {
				int blue = image.at<Vec3b>(r, c)[0];
				int green = image.at<Vec3b>(r, c)[1];
				int red = image.at<Vec3b>(r, c)[2];
				int total = blue + green + red;

				image.at<Vec3b>(r, c)[0] = total / 3;
				image.at<Vec3b>(r, c)[1] = total / 3;
				image.at<Vec3b>(r, c)[2] = total / 3;
			}
		}
	}
}

void BlackWhite::thresholdImage(Mat& imgHSV, Mat& image) {
	switch (currentColor) {
		case 0: // black
			inRange(imgHSV, Scalar(0, 150, 60), Scalar(0, 255, 255), image);
			break;
		case 1: // red
			inRange(imgHSV, Scalar(120, 150, 60), Scalar(179, 255, 255), image);
			break;
		case 2: // blue
			inRange(imgHSV, Scalar(85, 150, 60), Scalar(130, 255, 255), image);
			break;
		case 3: // green
			inRange(imgHSV, Scalar(37, 60, 134), Scalar(108, 196, 225), image);
			break;
	}
}

void BlackWhite::nextColor() {
	currentColor = (currentColor + 1) % COLOR_COUNT;
}

void BlackWhite::lastColor() {
	currentColor = (COLOR_COUNT + currentColor - 1) % COLOR_COUNT;
}
