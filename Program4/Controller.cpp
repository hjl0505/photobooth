#include "Controller.h"

Controller::Controller()
{
	FaceRecognition FR;
	currentItem = '0';
}

// --------------------------------------- REFERENCE or just Mat?
// controls
// Adds correct photobooth item to the input image and returns the new image
// pre: valid input image, key is valid (0=9, w,a,s,d)
// post: new image returned with photobooth item
Mat& Controller::controls(Mat& image, char key) {

	switch (key) {
		case '0': // Nothing
			break;
		case '1': // Hat
			break;
		case '2': // Glasses
			break;
		case '3': // Mustache
			break;
		case 'w': // Next Option
			break;
		case 'd': // Last Option
			break;
		case 's': // Next Color
			break;
		case 'a': // Last Color
			break;
		default:
			break;
	}

	return image;
}


