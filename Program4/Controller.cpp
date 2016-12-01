// Controller.cpp
// Chris Knakal and Hyungjin Lee
// CSS 487 Program 4 -- Photobooth
// 11.19.2016
//
// Redirects user input to the appropriate functionalities of the photobooth

#include "Controller.h"

// Constructor
// Initializes variables
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
			nextOption();
			controls(image, lastItemKey);
			break;
		case 'a': // Last Option
			lastOption();
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
// pre: image is valid, in BGR format
// post: image returned with the photobooth item if face is detected
void Controller::getHat(Mat& image) {
	// get faces
	vector<Rect_<int>> faces; 
	faceRec.detectFaces(image, faces);

	// put hat on faces
	over.putHat(image, faces);
}

// getGlasses
// Calls overlay putGlasses function to add glasses into the image
// pre: image is valid, in BGR format
// post: image returned with the photobooth item if pair of eyes are detected
void Controller::getGlasses(Mat& image) {
	// get eyes
	vector<Rect_<int>> eyes;
	faceRec.detectEyes(image, eyes);

	// put glasses over eyes
	over.putGlasses(image, eyes);
}

// getMustache
// Calls overlay putMustache function to add mustache into the image
// pre: image is valid, in BGR format
// post: image returned with the photobooth item if mouth and nose is detected
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

// makeBW
// Calls BlackWhite makeBW function to convert image into greyscale
// pre: image is valid, in BGR format
// post: image returned in greyscale and selected Color if detected
void Controller::makeBW(Mat& image) {
	blackWhite.makeBW(image);
}

// pixelate
// Calls Pixelate pixelateFace function to pixelate face detected
// pre: image is valid, in BGR format
// post: image returned in greyscale and selected color, if the color is detected
void Controller::pixelate(Mat& image) {
	// get faces
	vector<Rect_<int>> faces;
	faceRec.detectFaces(image, faces);

	// pixelate faces
	for (int i = 0; i < faces.size(); i++) {
		pixelator.pixelateFace(image, faces[i]);
	}
}

// nextColor
// Calls appropriate nextColor function depending on the last Photobooth Item key
// pre: none
// post: if color is a valid option, next color on the lastItem is selected
void Controller::nextColor() {
	if (lastItemKey == '4') { // BlackWhite 
		blackWhite.nextColor();
	}
	else if (lastItemKey <= ' 3' && lastItemKey > '0') { // Hat, Glasses, Mustache
		over.nextColor();
	}
}

// lastColor
// Calls appropriate nextColor function depending on the last Photobooth Item key
// pre: none
// post: if color is a valid option, last color on the lastItem is selected
void Controller::lastColor() {
	if (lastItemKey == '4') { // BlackWhite
		blackWhite.lastColor();
	}
	else if (lastItemKey <= ' 3' && lastItemKey > '0') {  // Hat, Glasses, Mustache
		over.lastColor();
	}
}

// nextOption
// Calls appropriate nextOption function depending on the last Photobooth Item key
// pre: none
// post: if there are multiple options available for the last item, next option of the last item is selected
void Controller::nextOption() {
	if (lastItemKey == '6') { // Pixelate
		pixelator.nextOption();
	}
	else if(lastItemKey <= ' 3' && lastItemKey > '0') { // Hat, Glasses, Mustache
		over.nextOption();
	}
}

// lastOption
// Calls appropriate lastOption function depending on the last Photobooth Item key
// pre: none
// post: if there are multiple options available for the last item, next option of the last item is selected
void Controller::lastOption() {
	if (lastItemKey == '6') { // Pixelate
		pixelator.lastOption();
	}
	else if (lastItemKey <= ' 3' && lastItemKey > '0')  { // Hat, Glasses, Mustache
		over.lastOption();
	}
}