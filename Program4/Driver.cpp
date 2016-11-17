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
using namespace std;
using namespace cv;

// Global Variables
// Note: Make sure the file "haarcascade_frontalface_default.xml" is in your
//        project directory.
// The file can be found in "opencv/sources/data/haarcascades/haarcascade_frontalface_default.xml"

// Slower
string fn_haar = "haarcascade_frontalface_default.xml";

// Faster
string lbp_cascade = "lbpcascade_frontalface.xml";

int main(int argc, char* argv[])
{
	/*VideoCapture vid;
	if (!vid.open(0)) {			// 0 if single camera connected to computer 
		return 0;				// error opening video
	}

	for (;;) {
		Mat frame;
		vid >> frame;

		if (frame.empty()) {
			break; // end of video stream
		}

		imshow("THIS IS THE WEBCAM WINDOW", frame);

		if (waitKey(1) == 27) {
			break;				// ESC to end program
		}
	}*/
	return 0;
}