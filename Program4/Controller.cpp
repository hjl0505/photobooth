// Controller.cpp
// Chris Knakal and Hyungjin Lee
// CSS 487 Program 4 -- Photobooth
// 11.19.2016
//
// Redirects user input to the appropriate functionalities of the photobooth

#include "Controller.h"

// controls
// Adds correct photobooth item to the input image and returns the new image
// pre: valid input image, key is valid (0=9, w,a,s,d (lower case only))
// post: image returned with photobooth item
void Controller::controls(Mat& image, char key) {
	switch (key) {
		case '0': // Reset, do nothing
			break;
		case '1': // Hat
			getHat(image, key);
			break;
		case '2': // Glasses
			getGlasses(image, key);
			break;
		case '3': // Mustache
			getMustache(image, key);
			break;
		case 'w': // Next Option
			over.nextOption(image);
			break;
		case 'd': // Last Option
			over.lastOption(image);
			break;
		case 's': // Next Color
			over.nextColor(image);
			break;
		case 'a': // Last Color
			over.lastColor(image);
			break;
		default:
			break; // Did not match any of the current keys
				   // Do nothing
	}
}

// getHat
// Calls overlay putHat function to add a hat into the image
// pre: image is valid
// post: image returned with photobooth item if face is detected
void Controller::getHat(Mat& image) {
	cout << "Controller getHat called" << endl;

	// get faces
	vector<Rect_<int>> faces; 
	faceRec.detectFaces(image, faces);

	// put hat on faces
	over.putHat(image, faces);
}

// getGlasses
// Calls overlay putGlasses function to add glasses into the image
// pre: image is valid
// post: image returned with photobooth item if pair of eyes are detected
void Controller::getGlasses(Mat& image) {
	cout << "Controller getGlasses called" << endl;

	// get eyes
	vector<Rect_<int>> eyes;
	faceRec.detectEyes(image, eyes);

	// put glasses over eyes
	over.putGlasses(image, eyes);
}

// getMustache
// Calls overlay putMustache function to add mustache into the image
// pre: image is valid
// post: image returned with photobooth item if a face is detected
void Controller::getMustache(Mat& image) {
	cout << "Controller getMustache called" << endl;

	// get mouths
	vector<Rect_<int>> mouths;
	faceRec.detectMouth(image, mouths);

	// put mustache on faces
	over.putMustache(image, mouths);
}
