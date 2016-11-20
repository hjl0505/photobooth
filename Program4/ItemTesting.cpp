#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/core/cvstd.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdarg.h>

using namespace std;
using namespace cv;

// Global Variables
// Note: Make sure the file "haarcascade_frontalface_default.xml" is in your
//        project directory.
// The file can be found in "opencv/sources/data/haarcascades/haarcascade_frontalface_default.xml"

// Slower
string fn_haar = "haarcascade_frontalface_default.xml";

// Faster
string lbp_cascade = "cascade/lbpcascade_frontalface.xml";

void cvShowManyImages(char* title, int nArgs, ...) {

	// img - Used for getting the arguments
	IplImage *img;

	// [[DispImage]] - the image in which input images are to be copied
	IplImage *DispImage;

	int size;
	int i;
	int m, n;
	int x, y;

	// w - Maximum number of images in a row
	// h - Maximum number of images in a column
	int w, h;

	// scale - How much we have to resize the image
	float scale;
	int max;

	// If the number of arguments is lesser than 0 or greater than 12
	// return without displaying
	if (nArgs <= 0) {
		printf("Number of arguments too small....\n");
		return;
	}
	else if (nArgs > 12) {
		printf("Number of arguments too large....\n");
		return;
	}
	// Determine the size of the image,
	// and the number of rows/cols
	// from number of arguments
	else if (nArgs == 1) {
		w = h = 1;
		size = 300;
	}
	else if (nArgs == 2) {
		w = 2; h = 1;
		size = 300;
	}
	else if (nArgs == 3 || nArgs == 4) {
		w = 2; h = 2;
		size = 300;
	}
	else if (nArgs == 5 || nArgs == 6) {
		w = 3; h = 2;
		size = 200;
	}
	else if (nArgs == 7 || nArgs == 8) {
		w = 4; h = 2;
		size = 200;
	}
	else {
		w = 4; h = 3;
		size = 150;
	}

	// Create a new 3 channel image
	DispImage = cvCreateImage(cvSize(100 + size*w, 60 + size*h), 8, 3);

	// Used to get the arguments passed
	va_list args;
	va_start(args, nArgs);

	// Loop for nArgs number of arguments
	for (i = 0, m = 20, n = 20; i < nArgs; i++, m += (20 + size)) {

		// Get the Pointer to the IplImage
		img = va_arg(args, IplImage*);

		// Check whether it is NULL or not
		// If it is NULL, release the image, and return
		if (img == 0) {
			printf("Invalid arguments");
			cvReleaseImage(&DispImage);
			return;
		}

		// Find the width and height of the image
		x = img->width;
		y = img->height;

		// Find whether height or width is greater in order to resize the image
		max = (x > y) ? x : y;

		// Find the scaling factor to resize the image
		scale = (float)((float)max / size);

		// Used to Align the images
		if (i % w == 0 && m != 20) {
			m = 20;
			n += 20 + size;
		}

		// Set the image ROI to display the current image
		cvSetImageROI(DispImage, cvRect(m, n, (int)(x / scale), (int)(y / scale)));

		// Resize the input image and copy the it to the Single Big Image
		cvResize(img, DispImage);

		// Reset the ROI in order to display the next image
		cvResetImageROI(DispImage);
	}

	// Create a new window, and show the Single Big Image
	cvNamedWindow(title, 1);
	cvShowImage(title, DispImage);

	cvWaitKey();
	cvDestroyWindow(title);

	// End the number of arguments
	va_end(args);

	// Release the Image Memory
	cvReleaseImage(&DispImage);
}


int main(int argc, char* argv[])
{
/*	CascadeClassifier haar_cascade;
	haar_cascade.load(lbp_cascade);

	// open the default camera, use something different from 0 otherwise;
	// Check VideoCapture documentation.
	VideoCapture camera;
	if (!camera.open(0)) {
		return 0;
	}

	while (true) {
		Mat frame;
		camera >> frame;

		// end of video stream
		if (frame.empty()) break;

		// flip the frame for ease of use
		flip(frame, frame, 1);


		// Convert the current frame to grayscale:
		Mat gray;
		cvtColor(frame, gray, CV_BGR2GRAY);

		// Find the faces in the frame:
		vector< Rect_<int> > faces;
		haar_cascade.detectMultiScale(gray, faces);

		for (int i = 0; i < faces.size(); i++) {
			// get a face
			Rect face = faces[i];

			// draw a green rectangle around the detected face
			rectangle(frame, face, CV_RGB(0, 255, 0), 1);
		}

		// show text on the current frame
		putText(frame, "CSS487", Point(10, frame.rows - 40), FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(255, 255, 255)); 

		// show width and height
		string width = to_string(static_cast<int>(camera.get(CV_CAP_PROP_FRAME_WIDTH)));
		string height = to_string(static_cast<int>(camera.get(CV_CAP_PROP_FRAME_HEIGHT)));
		string dimensions = width + " x " + height;
		putText(frame, dimensions, Point(10, frame.rows - 20), FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(255, 255, 255));

		Mat mustache = imread("pictures/mustache1.jpg", IMREAD_COLOR);

		for (int r = 0; r < mustache.rows; r++) {
			for (int c = 0; c < mustache.cols; c++) {
				int tempBlue = mustache.at<Vec3b>(r, c)[0];
				int tempGreen = mustache.at<Vec3b>(r, c)[1];
				int tempRed = mustache.at<Vec3b>(r, c)[2];

				// try 145
				if (tempBlue < 255 && tempGreen < 255 && tempRed < 255) {
					frame.at<Vec3b>(r, c)[0] = mustache.at<Vec3b>(r, c)[0];
					frame.at<Vec3b>(r, c)[1] = mustache.at<Vec3b>(r, c)[1];
					frame.at<Vec3b>(r, c)[2] = mustache.at<Vec3b>(r, c)[2];
				}
			}
		}



		// project camera images
		imshow("CSS487 Photobooth", frame);
		//imshow("CSS487 Photobooth", mustache);

		// stop capturing by pressing ESC
		if (waitKey(1) == 27) break;			
	}*/
	


	//cvShowManyImages("Image", 2, img5, img6);
	
	Mat bigImage = imread("pictures/background.jpg",IMREAD_COLOR);
	Mat lilImage = imread("pictures/mustache1.jpg", IMREAD_GRAYSCALE);

	Mat insetImage(bigImage);
	resize(lilImage, lilImage, Size(), 2, 2);
	//lilImage.copyTo(bigImage);
	Mat betterlil = imread("pictures/mustache1.jpg", IMREAD_GRAYSCALE);
	resize(lilImage, lilImage, Size(), 0.25, 0.25);

	threshold(lilImage, betterlil, 128, 255, THRESH_BINARY);
	int row = lilImage.rows;
	int col = lilImage.cols;
	Mat bw_mustache(row, col, CV_8UC3, Scalar(0,0,0));

	for (int r = 0; r < betterlil.rows; r++) {
		for (int c = 0; c < betterlil.cols; c++) {
			int tempbw = betterlil.at<uchar>(r, c);
				
			if (tempbw == 255) {
				bw_mustache.at<Vec3b>(r, c)[0] = 255;
				bw_mustache.at<Vec3b>(r, c)[1] = 255;
				bw_mustache.at<Vec3b>(r, c)[2] = 255;
			}

				//cout << r << " " << c << " " << tempGrey << endl;
				//cout << tempbw << endl;
		}
	}
	

	for (int r = 0; r < lilImage.rows; r++) {
		for (int c = 0; c < lilImage.cols; c++) {
			int tempBlue = bw_mustache.at<Vec3b>(r, c)[0];
			int tempGreen = bw_mustache.at<Vec3b>(r, c)[1];
			int tempRed = bw_mustache.at<Vec3b>(r, c)[2];

			// try 145
			if (tempBlue < 255 && tempGreen < 255 && tempRed < 255) {
				bigImage.at<Vec3b>(r, c)[0] = bw_mustache.at<Vec3b>(r, c)[0];
				bigImage.at<Vec3b>(r, c)[1] = bw_mustache.at<Vec3b>(r, c)[1];
				bigImage.at<Vec3b>(r, c)[2] = bw_mustache.at<Vec3b>(r, c)[2];
			}
		}
	}

	//imshow("Overlay Image", insetImage);
	imshow("Overlay Image", bigImage);
	//imshow("Overlay Image", betterlil);
	waitKey(0);


	return 0;
}