// FaceRecognition.h
// Chris Knakal and Hyungjin Lee
// CSS 487 Program 4 -- Photobooth
// 11.19.2016
//
// Attempts to find faces and facial features of a given image

#pragma once

#include "opencv2/objdetect.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/core/cvstd.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdarg.h>

using namespace std;
using namespace cv;

class FaceRecognition
{
public:
	// Constructors
	FaceRecognition();
	FaceRecognition(String face_path, String eye_path, String nose_path, String mouth_path);

	// Functions
	void detectFaces(Mat& image, vector<Rect_<int>>& faces);
	void detectEyes(Mat& image, vector<Rect_<int>>& eyes);
	void detectNose(Mat& image, vector<Rect_<int>>& noses);
	void detectMouth(Mat& image, vector<Rect_<int>>& mouths);

private:
	string face_cascade_path;
	string eye_cascade_path;
	string nose_cascade_path;
	string mouth_cascade_path;
	int test;
};

