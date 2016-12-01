#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "Controller.h"

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{

	Mat frame = imread("pictures/faces.jpg");
	resize(frame, frame, Size(), 0.25, 0.25);

	Controller cont;
	cont.controls(frame, '5');

	imshow("CSS487 Photobooth", frame);

	waitKey(0);
}