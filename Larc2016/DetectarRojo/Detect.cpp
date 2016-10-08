// The "Square Detector" program.
// It loads several images sequentially and tries to find squares in
// each image

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <math.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

#include <opencv2/core/utility.hpp>
//#include "opencv2/cudaobjdetect.hpp"
#include "opencv2/objdetect.hpp"

#include <ctime>
#include <raspicam/raspicam_cv.h>


using namespace cv;
using namespace std;

int main(int argc, char**argv){
	raspicam::RaspiCam_Cv Camera;
	Camera.set(CV_CAP_PROP_FORMAT, CV_8UC3);
	//Open camera
	Mat image;
	cout << "Opening Camera..." << endl;
	if (!Camera.open()) { cerr << "Error opening the camera" << endl; return -1; }
	namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

	int iLowH = 0;
	int iHighH = 179;

	int iLowS = 0;
	int iHighS = 255;

	int iLowV = 0;
	int iHighV = 255;

	//Create trackbars in "Control" window
	cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
	cvCreateTrackbar("HighH", "Control", &iHighH, 179);

	cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	cvCreateTrackbar("HighS", "Control", &iHighS, 255);

	cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
	cvCreateTrackbar("HighV", "Control", &iHighV, 255);

	while (true){
		Camera.grab();
		Camera.retrieve(image);
		 if(image.empty()) continue;
		//transpose(image, image); //dar vuelta la imagen
		//flip(image, image, 1);
		resize(image, image, Size(image.cols / 2, image.rows / 2)); // se achica para disminuir el calculo-> cambiar en camara vieja

		Mat imgHSV;

		cvtColor(image, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

		Mat imgThresholded;

		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

		//morphological opening (remove small objects from the foreground)
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		//morphological closing (fill small holes in the foreground)
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		imshow("Thresholded Image", imgThresholded); //show the thresholded image
		imshow("Original", image); //show the original image

		imshow("holi", image);
		if (waitKey(30)>0) {
			cout << "se ha presionado una tecla para cerrar" << endl;
			break;
		}
	}

	cout << "Stop camera..." << endl;
	Camera.release();
	return 0;

}