#include "opencv2/objdetect.hpp"#include "opencv2/videoio.hpp"#include <opencv2/core/core.hpp>#include <opencv2/core/cvstd.hpp>#include <opencv2/highgui/highgui.hpp>#include <opencv2/imgproc/imgproc.hpp>#include <opencv2/objdetect/objdetect.hpp>#include <string>#include <iostream>#include <stdio.h>using namespace std;using namespace cv;// Global Variables// Note: Make sure the file "haarcascade_frontalface_default.xml" is in your//        project directory.// The file can be found in "opencv/sources/data/haarcascades/haarcascade_frontalface_default.xml"// Slowerstring fn_haar = "haarcascade_frontalface_default.xml";// Fasterstring lbp_cascade = "lbpcascade_frontalface.xml";int main(int argc, char** argv){	CascadeClassifier haar_cascade;	haar_cascade.load(lbp_cascade);	VideoCapture camera;	// open the default camera, use something different from 0 otherwise;	// Check VideoCapture documentation.	if (!camera.open(0))		return 0;	while (true)	{		Mat frame;		camera >> frame;		// end of video stream		if (frame.empty()) break;		// flip the frame for ease of use		flip(frame, frame, 1);		// Convert the current frame to grayscale:		Mat gray;		cvtColor(frame, gray, CV_BGR2GRAY);		// Find the faces in the frame:		vector< Rect_<int> > faces;		haar_cascade.detectMultiScale(gray, faces);		for (int i = 0; i < faces.size(); i++) {			// get a face			Rect face = faces[i];			// draw a green rectangle around the detected face			rectangle(frame, face, CV_RGB(0, 255, 0), 1);		}		// show text on the current frame		putText(frame, "CSS487", Point(10, frame.rows - 40), FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(255, 255, 255));		// show width and height		string width = to_string(static_cast<int>(camera.get(CV_CAP_PROP_FRAME_WIDTH)));		string height = to_string(static_cast<int>(camera.get(CV_CAP_PROP_FRAME_HEIGHT)));		string dimensions = width + " x " + height;		putText(frame, dimensions, Point(10, frame.rows - 20), FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(255, 255, 255));		// project camera images		imshow("CSS487 Photobooth", frame);		// stop capturing by pressing ESC		if (waitKey(1) == 27) break;	}	return 0;}