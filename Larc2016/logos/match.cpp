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



int thresh = 50, N = 11;
const char* wndname = "Square Detection Demo";

HOGDescriptor hog(Size(64,64),Size(32,32),Size(32,32),Size(32,32),9);


// helper function:
// finds a cosine of angle between vectors
// from pt0->pt1 and from pt0->pt2
static double angle( Point pt1, Point pt2, Point pt0 )
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

// returns sequence of squares detected on the image.
// the sequence is stored in the specified memory storage
static void findSquares( const Mat& image, vector<vector<Point> >& squares )
{
    squares.clear();

    Mat pyr, timg, gray0(image.size(), CV_8U), gray;

    // down-scale and upscale the image to filter out the noise
    pyrDown(image, pyr, Size(image.cols/2, image.rows/2));
    pyrUp(pyr, timg, image.size());
    vector<vector<Point> > contours;

    // find squares in every color plane of the image
    for( int c = 0; c < 3; c++ )
    {
        int ch[] = {c, 0};
        mixChannels(&timg, 1, &gray0, 1, ch, 1);

        // try several threshold levels
        for( int l = 0; l < N; l++ )
        {
            // hack: use Canny instead of zero threshold level.
            // Canny helps to catch squares with gradient shading
            if( l == 0 )
            {
                // apply Canny. Take the upper threshold from slider
                // and set the lower to 0 (which forces edges merging)
                Canny(gray0, gray, 0, thresh, 5);
                // dilate canny output to remove potential
                // holes between edge segments
                dilate(gray, gray, Mat(), Point(-1,-1));
            }
            else
            {
                // apply threshold if l!=0:
                //     tgray(x,y) = gray(x,y) < (l+1)*255/N ? 255 : 0
                gray = gray0 >= (l+1)*255/N;
            }

            // find contours and store them all as a list
            findContours(gray, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

            vector<Point> approx;

            // test each contour
            for( size_t i = 0; i < contours.size(); i++ )
            {
                // approximate contour with accuracy proportional
                // to the contour perimeter
                approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);

                // square contours should have 4 vertices after approximation
                // relatively large area (to filter out noisy contours)
                // and be convex.
                // Note: absolute value of an area is used because
                // area may be positive or negative - in accordance with the
                // contour orientation
                if( approx.size() == 4 &&
                    fabs(contourArea(Mat(approx))) > 1000 &&
                    isContourConvex(Mat(approx)) )
                {
                    double maxCosine = 0;

                    for( int j = 2; j < 5; j++ )
                    {
                        // find the maximum cosine of the angle between joint edges
                        double cosine = fabs(angle(approx[j%4], approx[j-2], approx[j-1]));
                        maxCosine = MAX(maxCosine, cosine);
                    }

                    // if cosines of all angles are small
                    // (all angles are ~90 degree) then write quandrange
                    // vertices to resultant sequence
                    if( maxCosine < 0.3 )
                        squares.push_back(approx);
                }
            }
        }
    }
}

static void selectSquares(const vector<vector<Point> >& squares,vector<vector<Point> > & sq, vector<Point>& centers ){
//dejar solo cuadrados no concentricos


	vector<vector<Point> > s_accepted;
	centers.clear();

    for( size_t i = 0; i < squares.size(); i++ )
    {
        const Point* p = &squares[i][0];

		float a=(p[0].x+p[1].x+p[2].x+p[3].x)/4;
		float b=(p[0].y+p[1].y+p[2].y+p[3].y)/4;
		Point c= Point (a,b);//center
		Point d= c-p[0];

		bool flag=false;

		for(size_t j=0; j<s_accepted.size();j++){
			const Point* p_ = &s_accepted[j][0];
			float a_=(p_[0].x+p_[1].x+p_[2].x+p_[3].x)/4;
			float b_=(p_[0].y+p_[1].y+p_[2].y+p_[3].y)/4;
			Point c_= Point (a_,b_);//center
			Point d_=c_-p_[0];

			double dist=norm(c-c_);

			if(dist<12)
			{
				if(norm(d)<norm(d_))
					flag=true;

				else{
					s_accepted.erase(s_accepted.begin()+j);
					centers.erase(centers.begin()+j);
						}

			}
		}
		if(!flag) {
			centers.push_back(c);
			vector<Point> orderS;

			//punto arriba y a la derecha
			for(int k=0;k<4;k++){
				if(p[k].x>=c.x && p[k].y<c.y){
					orderS.push_back(p[k]);
					continue;}
			}

			//punto abajo y a la derecha
			for(int k=0;k<4;k++){
				if(p[k].x>=c.x && p[k].y>=c.y){
					orderS.push_back(p[k]);
					continue;}
			}

			//punto abajo y a la izquierda
			for(int k=0;k<4;k++){
				if(p[k].x<c.x && p[k].y>=c.y){
					orderS.push_back(p[k]);
					continue;}
				}

			//punto arriba y a la izquierda
			for(int k=0;k<4;k++){
				if(p[k].x<c.x && p[k].y<c.y){
					orderS.push_back(p[k]);
					continue;}
				}

			s_accepted.push_back(orderS);

	}

    }


	sq= s_accepted;
}

static vector<Mat> drawSquares( Mat& image, const vector<vector<Point> >& squares)
{
	vector<Mat> images;
    for( size_t i = 0; i < squares.size(); i++ )
    {
        const Point* p = &squares[i][0];
		int n = (int)squares[i].size();
/*
		Point2f srcTri[3],dstTri[3];
		srcTri[0]=p[3];
		srcTri[1]=p[2];
		srcTri[2]=p[1];
		dstTri[0]=Point2f(0,0);
		dstTri[1]=Point2f(0,63);
		dstTri[2]=Point2f(63,63);

		Mat warp_mat=getAffineTransform(srcTri,dstTri);
		Mat dst;
		warpAffine(image,dst,warp_mat,image.size());
*/

		Point2f srcTri[4],dstTri[4];
		srcTri[0]=p[3];
		srcTri[1]=p[2];
		srcTri[2]=p[1];
		srcTri[3]=p[0];
		
		dstTri[0]=Point2f(0,0);
		dstTri[1]=Point2f(0,63);
		dstTri[2]=Point2f(63,63);
		dstTri[3]=Point2f(63,0);

		Mat warp_mat=getPerspectiveTransform(srcTri,dstTri);
		Mat dst; 
		warpPerspective(image,dst,warp_mat,image.size());
		cvtColor(dst,dst,CV_RGB2GRAY);
		

		Rect rect=Rect(0,0,64,64);
		dst=dst(rect);
		Mat small=Mat::zeros(Size(64,64),CV_8UC1);
		//threshold( dst,small, threshold_value, max_BINARY_value,threshold_type );

		//threshold(dst,small,70,255,0);
		threshold(dst,small,70,255,CV_THRESH_BINARY|CV_THRESH_OTSU);
		
		images.push_back(small);
		
		char num[21];
         sprintf(num,"%d",i);
        // imshow(num,small);
        
		polylines(image, &p, &n, 1, true, Scalar(255,0,0), 3, LINE_AA);


    }



	return images;

}

float Dist(vector<float> a, vector<float> b)
{
	return (float) compareHist(a,b,CV_COMP_CORREL);

}
/////////
/*
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
      //  if(image.empty()) break;
       	transpose(image,image); //dar vuelta la imagen
        flip(image,image,1);
        resize(image,image,Size(image.cols/2,image.rows/2)); // se achica para disminuir el calculo-> cambiar en camara vieja

        imshow("holi",image);
        if(waitKey(30)>0) {
			cout<<"se ha presionado una tecla para cerrar"<<endl;
			break;}
        }

    cout<<"Stop camera..."<<endl;
    Camera.release();
        return 0;

}*/


int main(int , char**)
{
	int fontFace=FONT_HERSHEY_SCRIPT_SIMPLEX;
	vector<vector<Point> > squares;
	vector<float> ders;
	vector<Point> locs;
	vector<float> ders2;
	vector<Point> locs2;
	vector<float> ders3;
	vector<Point> locs3;
	vector<int> type;
   	vector<Point> centers;

    raspicam::RaspiCam_Cv Camera;
   Camera.set( CV_CAP_PROP_FORMAT, CV_8UC3 );

    namedWindow( wndname, 1 );

  Mat image;
    cout<<"Opening Camera..."<<endl;
    if (!Camera.open()) {cerr<<"Error opening the camera"<<endl;return -1;}

	//seteos imagenes de muestra
	Mat leche = imread("leche.png", 1);
	cvtColor(leche,leche,CV_RGB2GRAY);
	Mat carga = imread("carga.png", 1);
	cvtColor(carga,carga,CV_RGB2GRAY);
	Mat vasos = imread("terrines.png", 1);
	cvtColor(vasos,vasos,CV_RGB2GRAY);

	resize(leche,leche,Size(64,64),0,0,INTER_LINEAR);
	resize(carga,carga,Size(64,64),0,0,INTER_LINEAR);
	resize(vasos,vasos,Size(64,64),0,0,INTER_LINEAR);
	
	threshold(leche,leche,100,255,0);
	threshold(carga,carga,100,255,0);
	threshold(vasos,vasos,100,255,0);
	imshow("leche",leche);
	imshow("carga",carga);
	imshow("vasos",vasos);
/*
	//calculos hogs imagenes de muestra
	hog.compute(leche,ders,Size(0,0),Size(0,0),locs);
	hog.compute(carga,ders2,Size(0,0),Size(0,0),locs2);
	hog.compute(vasos,ders3,Size(0,0),Size(0,0),locs3);
*/
	cout<<"size"<<ders.size()<<endl;
	
     while(true){
        Camera.grab();
        Camera.retrieve ( image);
        if(image.empty()) break;
        //transpose(image,image); //dar vuelta la imagen
        flip(image,image,-1);
        resize(image,image,Size(image.cols/2,image.rows/2)); // se achica para disminuir el calculo-> cambiar en camara vieja

	type.clear();
	squares.clear();
	
	centers.clear();

        findSquares(image, squares);
        selectSquares(squares,squares,centers);
       vector<Mat> trozos=drawSquares(image, squares);

       for(int j=0; j<trozos.size();j++){

            Mat res,res2,res3;
            bitwise_xor(trozos[j],leche,res);
            bitwise_xor(trozos[j],carga,res2);
            bitwise_xor(trozos[j],vasos,res3);
            //imshow(num,res);
            //cout<<j<<" "<<sum(res)/(255*64*64)<<endl;
            
            float D1=1-sum(res)[0]/(255*64*64);
            float D2=1-sum(res2)[0]/(255*64*64);
            float D3=1-sum(res3)[0]/(255*64*64);

            cout<<"dist"<<D1<<"/"<<D2<<"/"<<D3<<endl;

float um=0.75f;
            //if(D1<0.4f && D2<0.4f && D3<0.4f)
             //   type.push_back(0);
            //else 
            if(D1>D2 && D1>D3 && D1>um)
                {type.push_back(1);
		cout<<"clase 1"<<endl;}
            else if(D2>D1 && D2>D3 && D2>um)
                {type.push_back(2);
		cout<<"clase 2"<<endl;}
            else if(D3>um)
                {type.push_back(3);
		cout<<"clase 3"<<endl;}
            else
		type.push_back(0);

            cout<<"clase "<< type[j]<<endl;
            cout<<"cx"<<centers[j].x<<"cy"<<centers[j].y<<"Area"<<contourArea(squares[j],false)<<endl;
            float errorx=(centers[j].x-(float)image.cols/2)/(float)image.cols/2;
            float errory=(centers[j].y-(float)image.rows/2)/(float)image.rows/2;
            cout<<"ex"<<errorx<<"ey"<<errory<<endl;

            char num[21];
            sprintf(num,"%d",type[j]);
            putText(image,num,centers[j],fontFace,2,Scalar::all(255),3,8);
            



        }


	resize(image,image,Size(image.cols,image.rows)); // se achica para disminuir el calculo-> cambiar en camara vieja

            imshow(wndname,image);
	if(waitKey(3)>0) break;
        }

    cout<<"Stop camera..."<<endl;
    Camera.release();
        return 0;
}

