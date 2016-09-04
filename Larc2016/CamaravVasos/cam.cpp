/*#include <ctime>
#include <iostream>
#include <raspicam/raspicam_cv.h>
using namespace std; 
 
int main ( int argc,char **argv ) {
   
    time_t timer_begin,timer_end;
    raspicam::RaspiCam_Cv Camera;
    cv::Mat image;
    int nCount=100;
    //set camera params
    Camera.set( CV_CAP_PROP_FORMAT, CV_8UC1 );
    //Open camera
    cout<<"Opening Camera..."<<endl;
    if (!Camera.open()) {cerr<<"Error opening the camera"<<endl;return -1;}
    //Start capture
    cout<<"Capturing "<<nCount<<" frames ...."<<endl;
    time ( &timer_begin );
    for ( int i=0; i<nCount; i++ ) {
        Camera.grab();
        Camera.retrieve ( image);
        if ( i%5==0 )  cout<<"\r captured "<<i<<" images"<<std::flush;
    }
    cout<<"Stop camera..."<<endl;
    Camera.release();
    //show time statistics
    time ( &timer_end ); 
    // get current time; same as: timer = time(NULL)  
    double secondsElapsed = difftime ( timer_end,timer_begin );
    cout<< secondsElapsed<<" seconds for "<< nCount<<"  frames : FPS = "<<  ( float ) ( ( float ) ( nCount ) /secondsElapsed ) <<endl;
    //save image 
    cv::imwrite("raspicam_cv_image.jpg",image);
    cout<<"Image saved at raspicam_cv_image.jpg"<<endl;
}

*/

#include <ctime>
#include <iostream>
#include <raspicam/raspicam_cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char **argv) {
    time_t timer_begin, timer_end;
    raspicam::RaspiCam_Cv Camera;

    Mat image;
    int nCount = 1000;
    string wname = "ICARO";

    // create a simple window to display the video
    namedWindow(wname, WINDOW_AUTOSIZE); // Create a window for display.

    //set camera params
    Camera.set(CV_CAP_PROP_FORMAT, CV_8UC3);
    //Open camera
    cout << "Opening Camera..." << endl;
    if (!Camera.open()) {
        cerr << "Error opening the camera" << endl;
        return -1;
    }

    //Start capture
    cout << "Capturing " << nCount << " frames ...." << endl;
    time(&timer_begin);

    for (int i = 0; i < nCount; i++) {
        Camera.grab();
        Camera.retrieve(image);
        imshow(wname, image);

        cout << "\r captured " << i << " images" << std::flush;
        waitKey(1);
    }
    cout << "Stop camera..." << endl;
    Camera.release();
    //show time statistics
    time(&timer_end); /* get current time; same as: timer = time(NULL)  */

    double secondsElapsed = difftime(timer_end, timer_begin);
    cout << secondsElapsed << " seconds for " << nCount << "  frames : FPS = " << (float) ((float) (nCount) / secondsElapsed) << endl;

/*
    // save image 
    cv::imwrite("raspicam_cv_image.jpg", image);
    cout << "Image saved at raspicam_cv_image.jpg" << endl;
*/
    waitKey(0);

}


/*

// to compile: g++ -o main main.cpp -lraspicam_cv -lraspicam `pkg-config --libs opencv`




#include <iostream>
#include <raspicam/raspicam_cv.h>
#include <exception>
#include <stdexcept>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


#include "opencv2/imgcodecs.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core/utility.hpp"

#include "opencv2/videoio/videoio_c.h"

using namespace std; 
using namespace cv;

Mat Raspi_Capture()
{
    raspicam::RaspiCam_Cv tCamera;

    cv::Mat tCapturedImage;

    int tFrameCount = 1;

    //Get an 8 bit single channel image (greyscale image)
    // this property needs to be set BEFORE the camera is opened
    tCamera.set(CV_CAP_PROP_FORMAT, CV_8UC1);

    if (!tCamera.open()) 
    {
        runtime_error tError("[Raspi_Capture] Camera failed to open");
        throw tError;
    }

    //edited code: I set every property that implements any kind of automatic adjustment to a manual value

    //these properties need to be set AFTER the camera is opened

    tCamera.set(CV_CAP_PROP_GAIN, 50); // values range from 0 to 100
    tCamera.set(CV_CAP_PROP_EXPOSURE, 50); //-1 is auto, values range from 0 to 100
    tCamera.set(CV_CAP_PROP_WHITE_BALANCE_RED_V, 50); //values range from 0 to 100, -1 auto whitebalance
    tCamera.set(CV_CAP_PROP_WHITE_BALANCE_BLUE_U, 50); //values range from 0 to 100,  -1 auto whitebalance


    tCamera.grab();
    tCamera.retrieve(tCapturedImage);


    tCamera.release();

    return tCapturedImage;
}

int main() 
{   
    Mat tImage;
    cvNamedWindow( "result", 1 );
	
    try
    {   
        
	while(true)
		tImage = Raspi_Capture();
        //imwrite("raw_image.png", tImage);
        cv::imshow("result",tImage); 
    }

    catch(runtime_error& tError)
    {
        cerr << "Error: " << tError.what() << endl;
    }

    return 0;
}
*/
