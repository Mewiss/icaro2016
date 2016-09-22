
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


int sliderPos = 0;

Mat image;

void processImage(int, void*);


int main(int argc,char**argv){
    raspicam::RaspiCam_Cv Camera;
   Camera.set( CV_CAP_PROP_FORMAT, CV_8UC3 );
    //Open camera
    Mat image;
    cout<<"Opening Camera..."<<endl;
    if (!Camera.open()) {cerr<<"Error opening the camera"<<endl;return -1;}

    while(true){
           Camera.grab();
        Camera.retrieve ( image);
        if(image.empty()) continue;
       	transpose(image,image); //dar vuelta la imagen
        flip(image,image,1);
        resize(image,image,Size(image.cols/2,image.rows/2)); // se achica para disminuir el calculo-> cambiar en camara vieja

        imshow("holi",image);
	namedWindow("result", 1);

    processImage();

        if(waitKey(30)>0) {
			cout<<"se ha presionado una tecla para cerrar"<<endl;
			break;}
        }

    cout<<"Stop camera..."<<endl;
    Camera.release();
        return 0;

}