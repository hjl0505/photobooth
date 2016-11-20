#include "Driver.h"
#include "FaceRecognition.h"

Driver::Driver()
{
}

int main(int argc, char* argv[])
{
	FaceRecognition FR;

	// Use Default Camera (0)
	VideoCapture camera;
	if (!camera.open(0)) {
		return 0;
	}

	while (true) {
		Mat frame;
		camera >> frame;

		// end of video stream
		if (frame.empty()) break;

		// flip the frame for ease of use
		flip(frame, frame, 1);

		// Detect faces and facial features
		vector<Rect_<int>> faces;
		vector<Rect_<int>> eyes;
		vector<Rect_<int>> noses;
		vector<Rect_<int>> mouths;

		//FR.detectFaces(frame, faces);
		FR.detectEyes(frame, eyes);
		//FR.detectNose(frame, noses);
		//FR.detectMouth(frame, mouths);

		/*for (int i = 0; i < faces.size(); i++) {
			Rect face = faces[i];
			rectangle(frame, face, CV_RGB(0, 255, 0), 1);
		} */

		cout << eyes.size() << endl;
		for (int i = 0; i < eyes.size(); i++) {
			Rect e = eyes[i];
			//circle(frame, Point(e.x + e.width / 2, e.y + e.height / 2), 3, Scalar(0, 255, 0), -1, 8);
			rectangle(frame, e, CV_RGB(0, 255, 0), 1);
		}

		/*for (int i = 0; i < noses.size(); i++) {
			Rect n = noses[i];
			circle(frame, Point(n.x + n.width / 2, n.y + n.height / 2), 3, Scalar(0, 255, 0), -1, 8);
		}

		for (int i = 0; i < mouths.size(); i++) {
			Rect m = mouths[i];
			rectangle(frame, Point(m.x, m.y), Point(m.x + m.width, m.y + m.height), Scalar(0, 255, 0), 1, 4);
		}*/




		// project camera images
		imshow("CSS487 Photobooth", frame);

		// stop capturing by pressing ESC
		if (waitKey(1) == 27) break;
	}
}
