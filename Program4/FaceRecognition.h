// FaceRecognition.h
// Chris Knakal and Hyungjin Lee
// CSS 487 Program 4 -- Photobooth
// 11.19.2016
//
// Attempts to find faces and facial features of a given image

#pragma once
#include "opencv2/objdetect.hpp"

using namespace std;
using namespace cv;

class FaceRecognition
{
public:
	// Constructors
	FaceRecognition();
	FaceRecognition(const String face_path, const String eye_path, const String nose_path, const String mouth_path);

	// Functions
	void detectFaces(const Mat& image, vector<Rect_<int>>& faces);
	void detectEyes(const Mat& image, vector<Rect_<int>>& eyes);
	void detectNose(const Mat& image, vector<Rect_<int>>& noses);
	void detectMouth(const Mat& image, vector<Rect_<int>>& mouths);

private:
	// Helper Function
	bool checkInBound(const Rect big, const Rect small);

	// Variables
	string face_cascade_path;
	string eye_cascade_path;
	string nose_cascade_path;
	string mouth_cascade_path;
};

