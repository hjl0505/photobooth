// FaceRecognition.cpp
// Chris Knakal and Hyungjin Lee
// CSS 487 Program 4 -- Photobooth
// 11.19.2016
//
// Attempts to find faces and facial features of a given image

#include "FaceRecognition.h"

// default constructor
// initialize cascade paths to default
FaceRecognition::FaceRecognition()
{
	face_cascade_path = "cascade/lbpcascade_frontalface.xml";
	eye_cascade_path = "cascade/Eyes.xml";
	nose_cascade_path = "cascade/Nose.xml";
	mouth_cascade_path = "cascade/Mouth.xml";
}

// constructor
// initialize cascade paths to given parameters
FaceRecognition::FaceRecognition(const String face_path, const String eye_path, const String nose_path, const String mouth_path) {
	face_cascade_path = face_path;
	eye_cascade_path = eye_path;
	nose_cascade_path = nose_path;
	mouth_cascade_path = mouth_path;
}

// detectFaces
// detect faces in the image and returns list of location of faces as rectangles
// pre: image and vector passed in are valid
// post: vector list contains rectangles that encompass faces in the image
void FaceRecognition::detectFaces(const Mat& image, vector<Rect_<int>>& faces) {
	CascadeClassifier face_cascade;
	face_cascade.load(face_cascade_path);

	face_cascade.detectMultiScale(image, faces, 1.15, 3, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
}

// detectEyes
// detects eyes in the image within bounds of detected faces
// pre: image and vector passed in are valid
// post: vector list contains rectangles that encompass eyes in the image
void FaceRecognition::detectEyes(const Mat& image, vector<Rect_<int>>& eyes) {

	// detects faces in the image
	vector<Rect_<int> > faces;
	detectFaces(image, faces);

	// detects eyes in the faces detected
	for (int i = 0; i < faces.size(); i++) { 
		// initialize ROI (region of interest)
		Rect face = faces[i];
		Mat ROI = image(Rect(face.x, face.y, face.width, face.height));

		// detect eyes in the ROI
		vector<Rect_<int> > tempEyes;
		CascadeClassifier eyes_cascade;
		eyes_cascade.load(eye_cascade_path);
		eyes_cascade.detectMultiScale(ROI, tempEyes, 1.20, 5, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

		// add displacement of the face to each eye position
		for (int j = 0; j < tempEyes.size(); j++) {
			Rect eye = tempEyes[j];
			eye.x += face.x;
			eye.y += face.y;
			eyes.push_back(eye);
		}
	}
}

// detectNose
// detects nose in the image within bounds of detected faces
// pre: image and vector passed in are valid
// post: vector list contains rectangles that encompass nose in the image
void FaceRecognition::detectNose(const Mat& image, vector<Rect_<int>>& noses) {
	// detects faces in the image
	vector<Rect_<int> > faces;
	detectFaces(image, faces);

	// detects nose in the faces detected
	for (int i = 0; i < faces.size(); i++) {   
		// initialize ROI (region of interest)
		Rect face = faces[i];
		Mat ROI = image(Rect(face.x, face.y, face.width, face.height));

		// detect nose in the ROI
		vector<Rect_<int> > tempNoses;
		CascadeClassifier nose_cascade;
		nose_cascade.load(nose_cascade_path);
		nose_cascade.detectMultiScale(ROI, tempNoses, 1.20, 5, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

		// add displacement of the face to each nose position
		for (int j = 0; j < tempNoses.size(); j++) {
			Rect nose = tempNoses[j];
			nose.x += face.x;
			nose.y += face.y;
			noses.push_back(nose);
		}
	}
}

// detectMouth
// detects mouth in the image within bounds of detected faces
// pre: image and vector passed in are valid
// post: vector list contains rectangles that encompass mouths in the image
void FaceRecognition::detectMouth(const Mat& image, vector<Rect_<int>>& mouths) {
	// detects faces in the image
	vector<Rect_<int> > faces;
	detectFaces(image, faces);

	// detects mouth in the faces detected
	for (int i = 0; i < faces.size(); i++) {   
		// initialize ROI (region of interest)
		Rect face = faces[i];
		Mat ROI = image(Rect(face.x, face.y, face.width, face.height));

		// detect mouths in the ROI
		vector<Rect_<int> > tempMouths;
		CascadeClassifier mouth_cascade;
		mouth_cascade.load(mouth_cascade_path);
		mouth_cascade.detectMultiScale(ROI, tempMouths, 1.20, 5, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

		vector<Rect_<int> > tempNoses;
		detectNose(image, tempNoses);

		// add displacement of the face to each mouth position
		for (int j = 0; j < tempMouths.size(); j++) {
			Rect mouth = tempMouths[j];
			mouth.x += face.x;
			mouth.y += face.y;
			mouths.push_back(mouth);
		}
	}
}

// checkInBound
// checks to see if smalll rectangle is inside the big rectangle
// pre: big and small rectangle are valid
// post: returns true if small rectangle is inside big rectangle
bool FaceRecognition::checkInBound(const Rect big, const Rect small) {
	int bigLx = big.x;
	int bigUy = big.y;
	int bigRx = big.x + big.width;
	int bigDy = big.y + big.height;

	int smLx = small.x;
	int smUy = small.y;
	int smRx = small.x + small.width;
	int smDy = small.y + small.height;

	if (smLx > bigLx && smRx < bigRx) {
		if (smUy > bigUy && smDy < bigDy) {
			return true;
		}
	}
	return false;
}
