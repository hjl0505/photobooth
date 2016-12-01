// Controller.cpp
// Chris Knakal and Hyungjin Lee
// CSS 487 Program 4 -- Photobooth
// 11.19.2016
//
// Redirects user input to the appropriate functionalities of the photobooth

#include "Controller.h"

Controller::Controller() {
	lastItemKey = 0;
}

// controls
// Adds correct photobooth item to the input image and returns the new image
// pre: valid input image, key is valid (0=9, w,a,s,d (lower case only))
// post: image returned with photobooth item
void Controller::controls(Mat& image, char key) {
	switch (key) {
		case '0': // Reset, do nothing
			lastItemKey = key;
			break;
		case '1': // Hat
			lastItemKey = key;
			getHat(image);
			break;
		case '2': // Glasses
			lastItemKey = key;
			getGlasses(image);
			break;
		case '3': // Mustache
			lastItemKey = key;
			getMustache(image);
			break;
		case '4': // black and white
			lastItemKey = key;
			makeBW(image);
			break;
		case '5': // faceswap
			lastItemKey = key;
			swapper.swap(image);
			break;
		case '6': // pixelate
			lastItemKey = key;
			pixelate(image);
			break;
		case 'd': // Next Option
			over.nextOption();
			controls(image, lastItemKey);
			break;
		case 'a': // Last Option
			over.lastOption();
			controls(image, lastItemKey);
			break;
		case 'w': // Next Color
			nextColor();
			controls(image, lastItemKey);
			break;
		case 's': // Last Color
			lastColor();
			controls(image, lastItemKey);
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
	// get mouths
	vector<Rect_<int>> mouths;
	faceRec.detectMouth(image, mouths);

	// get noses
	vector<Rect_<int>> noses;
	faceRec.detectNose(image, noses);

	// put mustache on faces
	over.putMustache(image, mouths, noses);
}

void Controller::makeBW(Mat& image) {
	blackWhite.makeBW(image);
}

void Controller::nextColor() {
	if (lastItemKey == '4') {
		blackWhite.nextColor();
	}
	else {
		over.nextColor();
	}
}

void Controller::lastColor() {
	if (lastItemKey == '4') {
		blackWhite.lastColor();
	}
	else {
		over.lastColor();
	}
}

void Controller::pixelate(Mat& image) {
	// get faces
	vector<Rect_<int>> faces;
	faceRec.detectFaces(image, faces);

	for (int i = 0; i < faces.size(); i++) {
		pixelator.pixelator(image, faces[i]);
	}

}
