#include "FaceRecognition.h"

FaceRecognition::FaceRecognition()
{
	test = 5;
	face_cascade_path = "cascade/lbpcascade_frontalface.xml";
	eye_cascade_path = "cascade/Eyes.xml";
	nose_cascade_path = "cascade/Nose.xml";
	mouth_cascade_path = "cascade/Mouth.xml";
}

FaceRecognition::FaceRecognition(String face_path, String eye_path, String nose_path, String mouth_path) {
	face_cascade_path = face_path;
	eye_cascade_path = eye_path;
	nose_cascade_path = nose_path;
	mouth_cascade_path = mouth_path;
}

void FaceRecognition::detectFaces(Mat& image, vector<Rect_<int>>& faces) {
	CascadeClassifier face_cascade;
	face_cascade.load(face_cascade_path);

	face_cascade.detectMultiScale(image, faces, 1.15, 3, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
}

void FaceRecognition::detectEyes(Mat& image, vector<Rect_<int>>& eyes) {
	vector<Rect_<int> > faces;
	detectFaces(image, faces);

	CascadeClassifier eyes_cascade;
	eyes_cascade.load(eye_cascade_path);

	for (int i = 0; i < faces.size(); i++) {
		// Eyes should be detected inside of a face
		Rect face = faces[i];
		Mat ROI = image(Rect(face.x, face.y, face.width, face.height));

		// Detect eyes
		eyes_cascade.detectMultiScale(ROI, eyes, 1.20, 5, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
	}
}

void FaceRecognition::detectNose(Mat& image, vector<Rect_<int>>& noses) {
	CascadeClassifier nose_cascade;
	nose_cascade.load(nose_cascade_path);

	nose_cascade.detectMultiScale(image, noses, 1.20, 5, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
}

void FaceRecognition::detectMouth(Mat& image, vector<Rect_<int>>& mouths) {
	CascadeClassifier mouth_cascade;
	mouth_cascade.load(mouth_cascade_path);

	mouth_cascade.detectMultiScale(image, mouths, 1.20, 5, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
}

