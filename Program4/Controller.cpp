#include "Controller.h"

Controller::Controller()
{
}

// --------------------------------------- REFERENCE or just Mat?
// controls
// Adds correct photobooth item to the input image and returns the new image
// pre: valid input image, key is valid (0=9, w,a,s,d)
// post: image returned with photobooth item
void Controller::controls(Mat& image, char key) {
	
	switch (key) {
		case '0': // Reset, do Nothing
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
			break;
	}
}

void Controller::getHat(Mat& image, char key) {
	cout << "Controller getHat called" << endl;

	// get faces
	vector<Rect_<int>> faces; 
	faceRec.detectFaces(image, faces);

	// put hat on faces
	over.putHat(image, faces);
}

void Controller::getGlasses(Mat& image, char key) {
	cout << "Controller getGlasses called" << endl;

	// get eyes
	vector<Rect_<int>> eyes;
	faceRec.detectEyes(image, eyes);

	// put glasses over eyes
	over.putGlasses(image, eyes);
}

void Controller::getMustache(Mat& image, char key) {
	cout << "Controller getMustache called" << endl;

	// get mouths
	vector<Rect_<int>> mouths;
	faceRec.detectMouth(image, mouths);

	// put mustache on faces
	over.putMustache(image, mouths);
}
