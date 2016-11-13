#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;

// From: http://answers.opencv.org/question/1/how-can-i-get-frames-from-my-webcam/

int main(int argc, char** argv)
{
	VideoCapture cap;
	// open the default camera, use something different from 0 otherwise;
	// Check VideoCapture documentation.
	if (!cap.open(0))
		return 0;
	for (;;)
	{
		Mat frame;
		cap >> frame;
		if (frame.empty()) break; // end of video stream
		imshow("this is you, smile! :)", frame);
		if (waitKey(1) == 27) break; // stop capturing by pressing ESC 
	}
	// the camera will be closed automatically upon exit
	// cap.close();
	return 0;
}