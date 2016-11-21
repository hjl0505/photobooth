#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "Controller.h"

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	// Use Default Camera (0)
	VideoCapture camera;
	if (!camera.open(0)) {
		return 0;
	}

	// Initialize Controller
	Controller cont;

	char lastKey = '0'; // 0: reset, 1: hat, 2: glasses, 3: mustache
	char key;

	// Start photobooth
	while (true) {
		Mat frame;
		camera >> frame;

		// End of video stream
		if (frame.empty()) break;

		// Flip the frame for ease of use
		flip(frame, frame, 1);

		// Project camera images
		imshow("CSS487 Photobooth", frame);

		// GET ASCII key code for controls (0-9)
		// Stop capturing with ESC
		key = waitKey(1);
		if (key == 27) {
			break;
		}
		else if ((key >= '0' && key <= '9') || key == 'w' || key == 'a' ||  key == 's' || key == 'd') {
			// get photobooth item with new key
			lastKey = key;
			cont.controls(frame, key);
		}
		else {
			// continue photobooth with last key
			cont.controls(frame, lastKey);
		}
	}
}
