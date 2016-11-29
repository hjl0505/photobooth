#include "BlackWhite.h"

void BlackWhite::makeBW(Mat& image) {
	//Convert the captured frame from BGR to HSV
	Mat imgHSV;
	cvtColor(image, imgHSV, COLOR_BGR2HSV);




	//Threshold the image to RED
	Mat imgThresholded;
	inRange(imgHSV, Scalar(120, 150, 60), Scalar(179, 255, 255), imgThresholded); 




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
