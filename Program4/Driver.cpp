// Driver.cpp
// Chris Knakal and Hyungjin Lee
// CSS 487 Program 4 -- Photobooth
// 11.19.2016
//
// Starts the photobooth program
// Displays webcam frames and reads input from the user
// key input 0: resets the photobooth
// key input 1: places HAT on the faces detected in the webcam frame
// key input 2: places GLASSES on pairs of eyes detected in the webcam frame
// key input 3: places MUSTACHE on the mouth/nose detected in the webcam frame
// key input 4: converts webcam frame into GREYSCALE, except for the selected color
// key input 5: FACE SWAPs 2 faces
// key input 6: PIXELATEs face detected in the webcam frame
// key input w/s: changes colors for the previous items (1-4)
// key input a/d: changes options for the previous items (1-3, 6)

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "Controller.h"

using namespace std;
using namespace cv;

// main
// Starts the webcam and photobooth program
// pre: none
// post: starts/ends interactive photobooth proram
int main(int argc, char* argv[])
{
	// Use Default Camera (0)
	VideoCapture camera;
	if (!camera.open(0)) {
		return 0;
	}

	// Initialize Controller
	Controller cont;

	// store user input for photobooth key, and previous key
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

		// GET ASCII key code for controls (0-9), w, a, s, d
		// Stop capturing with ESC
		key = waitKey(1);
		if (key == 27) { // ESC
			break;
		}
		else if ((key >= '0' && key <= '9')) { //photobooth item with new key
			lastKey = key;
			cont.controls(frame, key);
		}
		else if (key == 'w' || key == 'a' || key == 's' || key == 'd') { // new color or new option
			cont.controls(frame, key);
		}
		else { // continue photobooth with last key
			cont.controls(frame, lastKey);
		}

		// print the lastKey variable on the frame
		string keyString(1, lastKey);
		putText(frame, keyString, Point(10, frame.rows - 20), FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(255, 255, 255));

		// Project camera images
		imshow("CSS487 Photobooth", frame);
	}

}
