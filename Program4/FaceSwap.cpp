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
			int imgRow = r + faceTo.y;
			int imgCol = c + faceTo.x;

			int faceToMidX = faceTo.x + faceTo.width / 2;
			int faceToMidY = faceTo.y + faceTo.height / 2;
			int faceFromMidX = faceFrom.x + faceFrom.width / 2;
			int faceFromMidY = faceFrom.y + faceFrom.height / 2;

			bool insideEllipse = insideFaceEllipse(copyFace, faceTo, imgCol, imgRow, Point(faceToMidX, faceToMidY));
			if (insideEllipse) {
				if (imgRow < image.rows && imgCol < image.cols) {
					image.at<Vec3b>(imgRow, imgCol)[0] = copyFace.at<Vec3b>(r, c)[0];
					image.at<Vec3b>(imgRow, imgCol)[1] = copyFace.at<Vec3b>(r, c)[1];
					image.at<Vec3b>(imgRow, imgCol)[2] = copyFace.at<Vec3b>(r, c)[2];
				}
			}
			
		}
	}
}

bool FaceSwap::insideFaceEllipse(Mat& image, Rect faceTo, int curX, int curY, Point toCenter) {
	double a = ((curX - toCenter.x) * (curX - toCenter.x)) / ((faceTo.width / 4) * (faceTo.width / 3));
	double b = ((curY - toCenter.y) * (curY - toCenter.y)) / ((faceTo.height / 4) * (faceTo.height / 3));

	if (a + b <= 1) {
		return true;
	}
	return false;
}

int FaceSwap::getFaceWidth(Mat& face) {
	vector<Rect_<int>> eyes;
	faceRec.detectFaces(face, eyes);

	Rect leftEye, rightEye;

	if (eyes.size() >= 2) {
		if (eyes[0].x < eyes[1].x) {
			leftEye = eyes[0];
			rightEye = eyes[1];
		}
		else {
			leftEye = eyes[1];
			rightEye = eyes[0];
		}
	}
	return rightEye.x + rightEye.width - leftEye.x;
}

int FaceSwap::getFaceHeight(Mat& face) {
	vector<Rect_<int>> eyes;
	faceRec.detectFaces(face, eyes);

	Rect leftEye;

	if (eyes.size() >= 2) {
		if (eyes[0].x < eyes[1].x) {
			leftEye = eyes[0];
		}
		else {
			leftEye = eyes[1];
		}
	}

	vector<Rect_<int>> mouths;
	faceRec.detectMouth(face, mouths);

	if (mouths.size() >= 1) {
		return mouths[0].y - leftEye.y;
	}
	else return 0;
}

