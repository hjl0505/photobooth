// FaceSwap.cpp
// Chris Knakal and Hyungjin Lee
// CSS 487 Program 4 -- Photobooth
// 11.19.2016
//
// Attempts to swap two faces
// Uses rough oval shape to swap

#include "FaceSwap.h"

// swap
// detect faces in the image and swaps
// pre: image is valid, in BGR format
// post: image has 2 faces swapped
void FaceSwap::swap(Mat& image) {

	// get faces
	vector<Rect_<int>> faces;
	faceRec.detectFaces(image, faces);

	// get copy of the image to use to read face pixel information from
	Mat tempImage = image.clone();
	
	// swaps faces only if at least 2 faces were detected
	if (faces.size() >= 2) {
		Rect face1 = faces[0];
		Rect face2 = faces[1];

		// create separate face images
		Mat faceOne = tempImage(Rect(face1.x, face1.y, face1.width, face1.height));
		Mat faceTwo = tempImage(Rect(face2.x, face2.y, face2.width, face2.height));

		// resize the face images
		resize(faceOne, faceOne, Size(face2.width, face2.height));
		resize(faceTwo, faceTwo, Size(face1.width, face1.height));

		// second face onto first face
		swapHelper(image, faceTwo, face1, face2);
		// first face onto second face
		swapHelper(image, faceOne, face2, face1);
	}
}

// swapHelper
// copies the copyFace image onto the image if pixel is within a oval of the other face
// pre: images are valid in BGR format, face is resized to fit the new location
// post: copyFace is drawn on the image in the other face location
void FaceSwap::swapHelper(Mat& image, Mat& copyFace, Rect faceTo, Rect faceFrom) {
	for (int r = 0; r < copyFace.rows; r++) {
		for (int c = 0; c < copyFace.cols; c++) {
			// adjust position of face in image
			int imgRow = r + faceTo.y;
			int imgCol = c + faceTo.x;

			// calculate center point for both faces
			int faceToMidX = faceTo.x + faceTo.width / 2;
			int faceToMidY = faceTo.y + faceTo.height / 2;
			int faceFromMidX = faceFrom.x + faceFrom.width / 2;
			int faceFromMidY = faceFrom.y + faceFrom.height / 2;

			// check if current pixel is inside ellipse of the face to copy from
			bool insideEllipse = insideFaceEllipse(copyFace, faceTo, imgCol, imgRow, Point(faceToMidX, faceToMidY));

			if (insideEllipse) {
				// copy face 
				if (imgRow < image.rows && imgCol < image.cols) {
					image.at<Vec3b>(imgRow, imgCol)[0] = copyFace.at<Vec3b>(r, c)[0];
					image.at<Vec3b>(imgRow, imgCol)[1] = copyFace.at<Vec3b>(r, c)[1];
					image.at<Vec3b>(imgRow, imgCol)[2] = copyFace.at<Vec3b>(r, c)[2];
				}
			}
			
		}
	}
}

// insideFaceEllipse
// checks if current x, y point is within the ellipse of the face
// Equation: ((x - h) ^ 2 / rx ^ 2) + ((y - k) ^ 2 / ry ^ 2) <= 1
// pre: image is valid
// post: returns true if current point is within the ellipse
bool FaceSwap::insideFaceEllipse(Mat& image, Rect face, int curX, int curY, Point center) {
	double a = ((curX - center.x) * (curX - center.x)) / ((face.width / 4) * (face.width / 3));
	double b = ((curY - center.y) * (curY - center.y)) / ((face.height / 4) * (face.height / 3));

	if (a + b <= 1) {
		return true;
	}
	return false;
}

// getFaceWidth
// calculates face width using left of left eye and right of right eye
// pre: face image is valid
// post: returns width of the face if two eyes are detected
int FaceSwap::getFaceWidth(Mat& face) {
	// Detect eyes in the face
	vector<Rect_<int>> eyes;
	faceRec.detectFaces(face, eyes);

	Rect leftEye, rightEye;

	// check if at least 2 eyes are detected
	if (eyes.size() >= 2) {
		// determine which eye is left and right
		if (eyes[0].x < eyes[1].x) {
			leftEye = eyes[0];
			rightEye = eyes[1];
		}
		else {
			leftEye = eyes[1];
			rightEye = eyes[0];
		}
		// return the difference 
		return rightEye.x + rightEye.width - leftEye.x;
	}
	else return 0;
}


// getFaceHeight
// calculates face height using top of eye and bottom of mouth
// pre: face image is valid
// post: returns height of the face if an eye and a mouth is detected
int FaceSwap::getFaceHeight(Mat& face) {
	// detect eyes
	vector<Rect_<int>> eyes;
	faceRec.detectFaces(face, eyes);

	// get at least 1 eye
	if (eyes.size() > 0) {
		Rect eye = eyes[0];

		// detect mouth
		vector<Rect_<int>> mouths;
		faceRec.detectMouth(face, mouths);

		// get bottom of mouth and top of eye
		if (mouths.size() >= 1) {
			return mouths[0].y + mouths[0].height - eye.y;
		}
		else return 0;
	}
	else return 0;
}

