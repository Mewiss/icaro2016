
/*

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;

#define L 12

float angle(const Vec4i &v1){//calcula angulo con la vertical
    float s1=sqrt(1);
    float x=v1[0]-v1[2];
    float y=v1[1]-v1[3];
    float s2=sqrt(x*x+y*y);

    float dot=y;

    float a=dot/(s1*s2);

    if(a>=1.0)
        return 0.0;
    else if(a<=-1.0)
        return CV_PI;

    else
        return acos(a);
}


double dist(const Vec4i &v1,const Vec4i &v2){
    double a=(v1[3]-v1[1])/(v1[2]-v1[0]);
    double b=v1[1]-a*v1[0];

    return abs(a*v2[0]-v2[1]+b)/sqrt(pow(a,2)+1);

}


double minDist(vector<Vec4i> lines, Vec4i l0){
    double minD=10000;

        for( size_t i = 0; i < lines.size(); i++ )
        {
        Vec4i l = lines[i];
        double d=dist(l,l0);
        if(d>0 && d<minD)
            minD=d;
        }

}



static void help()
{
    cout << "\nThis program demonstrates line finding with the Hough transform.\n"
            "Usage:\n"
            "./houghlines <image_name>, Default is ../data/pic1.png\n" << endl;
}

int main(int argc, char** argv)
{
    const char* filename = "largo.jpg";//argc >= 2 ? argv[1] : "../data/pic1.png";

    Mat src = imread(filename, 1);
    if(src.empty())
    {
        help();
        cout << "can not open " << filename << endl;
        return -1;
    }




     // resize(src,src,Size(src.cols/3,src.rows/3));

  //  cvtColor(src,src, COLOR_BGR2GRAY);
   // threshold(src,src,100,100,2);


    Mat dst, cdst;
    Canny(src, dst, 50, 150, 3);
    cvtColor(dst, cdst, COLOR_GRAY2BGR);

    double cx,cy,A;

    vector<Vec4i> lines,vert,hor;
    vector<float> angles;

    HoughLinesP(dst, lines, 1, 2*CV_PI/180, 30, 10, 5 );

    for( size_t i = 0; i < lines.size(); i++ )
    {
        Vec4i l = lines[i];
        Point p1(l[0],l[1]);
        Point p2(l[2], l[3]);


        line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 2, LINE_AA);

        if(angle(l)>1.2 && angle(l)<2)
        {
        line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,0,0), 2, LINE_AA);
        vert.push_back(l);
                A=A+norm(p2-p1);

        cx=cx+norm(p2-p1)*(l[0]+l[2])/2;
        cy=cy+norm(p2-p1)*(l[1]+l[3])/2;

        angles.push_back(angle(l));}

       else if(angle(l)<0.15 )//|| angle(l)>1.9)
        {line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,255,0), 2, LINE_AA);
        hor.push_back(l);
                A=A+norm(p2-p1);

        cx=cx+norm(p2-p1)*(l[0]+l[2])/2;
        cy=cy+norm(p2-p1)*(l[1]+l[3])/2;
          angles.push_back(angle(l));}


    }

    if(vert.size()<L)
        cout<<"no hay vaca" << endl;

    cx=cx/A;
    cy=cy/A;

    circle(cdst,Point(cx,cy),10,Scalar(255,255,255),3,8,0);

 vector<double> distancias;

    vector<vector <Vec4i> > sel,sel2;


    size_t i=0;
    cout<<src.cols<<"x"<<src.rows<<endl;

    while(  i < vert.size() )
    {


        vector <Vec4i> s;

        s.push_back(vert[i]);

        size_t j=i+1;

        while(j<vert.size()){

            double d=dist(vert[i],vert[j]);

            if(abs(angle(vert[i])-angle(vert[j]))<0.02  && d<60)
            {

                 Vec4i l = vert[j];
                 s.push_back(vert[j]);
                vert.erase(vert.begin()+j);
               line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255-20*sel.size(),0,20*sel.size()), 2, LINE_AA);
            }

            else j++;
        }

        if(s.size()>1)
        {sel.push_back(s);
        vert.erase(vert.begin()+i);}

        else
            i++;


    }


    i=0;

    while(  i < hor.size() )
    {


        vector <Vec4i> s;

        s.push_back(hor[i]);

        size_t j=i+1;

        while(j<hor.size()){

              double d=dist(vert[i],vert[j]);

            if(abs(angle(vert[i])-angle(vert[j]))<0.02  && d<60)
            {

                 Vec4i l = hor[j];
                 s.push_back(hor[j]);
                hor.erase(hor.begin()+j);
               line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255-20*sel.size(),0,20*sel.size()), 2, LINE_AA);
            }

            else j++;
        }

        if(s.size()>1)
        {sel2.push_back(s);
        hor.erase(hor.begin()+i);}

        else
            i++;


    }



/*
    for(int j=0; j<sel.size(); j++){

        vector<Vec4i> paral=sel[j];

          for( size_t i = 0; i < paral.size(); i++ )
    {
        Vec4i l =paral[i];
        if(minDist(paral,l)<50)
        line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(100,100,100), 1, LINE_AA);
    }

    }

*/

 /*   cout<<sel.size() << endl;


    imshow("source", src);
    imshow("detected lines", cdst);

    waitKey();

    return 0;
}*/


/**
 * @function cornerHarris_Demo.cpp
 * @brief Demo code for detecting corners using Harris-Stephens method
 * @author OpenCV team
 */

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

/// Global variables
Mat src, src_gray;
int thresh = 200;
int max_thresh = 255;

const char* source_window = "Source image";
const char* corners_window = "Corners detected";

/// Function header
void cornerHarris_demo( int, void* );

/**
 * @function main
 */
int main( int, char** argv )
{
  /// Load source image and convert it to gray
  src = imread( argv[1], 1 );
  cvtColor( src, src_gray, COLOR_BGR2GRAY );

  /// Create a window and a trackbar
  namedWindow( source_window, WINDOW_AUTOSIZE );
  createTrackbar( "Threshold: ", source_window, &thresh, max_thresh, cornerHarris_demo );
  imshow( source_window, src );

  cornerHarris_demo( 0, 0 );

  waitKey(0);
  return(0);
}

/**
 * @function cornerHarris_demo
 * @brief Executes the corner detection and draw a circle around the possible corners
 */
void cornerHarris_demo( int, void* )
{

  Mat dst, dst_norm, dst_norm_scaled;
  dst = Mat::zeros( src.size(), CV_32FC1 );

  /// Detector parameters
  int blockSize = 2;
  int apertureSize = 3;
  double k = 0.04;

  /// Detecting corners
  cornerHarris( src_gray, dst, blockSize, apertureSize, k, BORDER_DEFAULT );

  /// Normalizing
  normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
  convertScaleAbs( dst_norm, dst_norm_scaled );

  /// Drawing a circle around corners
  for( int j = 0; j < dst_norm.rows ; j++ )
     { for( int i = 0; i < dst_norm.cols; i++ )
          {
            if( (int) dst_norm.at<float>(j,i) > thresh )
              {
               circle( dst_norm_scaled, Point( i, j ), 5,  Scalar(0), 2, 8, 0 );
              }
          }
     }
  /// Showing the result
  namedWindow( corners_window, WINDOW_AUTOSIZE );
  imshow( corners_window, dst_norm_scaled );
}


