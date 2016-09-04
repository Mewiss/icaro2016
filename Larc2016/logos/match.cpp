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

using namespace cv;
using namespace std;



int thresh = 50, N = 11;
const char* wndname = "Square Detection Demo";

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

static vector<vector<Point> > selectSquares(vector<vector<Point> >& squares ){
//dejar solo cuadrados no concentricos


	vector<vector<Point> > s_accepted;

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
		else		
			s_accepted.erase(s_accepted.begin()+j);
		}
	}
	if(!flag) {
	//c_accepted.push_back(c);
	//sizes.push_back(a+b);
	s_accepted.push_back(squares[i]);
	}
	
    }


	return  s_accepted;
}
// the function draws all the squares in the image 
static void drawSquares( Mat& image, const vector<vector<Point> >& squares )
{
	int j=0;
    for( size_t i = 0; i < squares.size(); i++ )
    {
	j++;
        const Point* p = &squares[i][0];
	
	int n = (int)squares[i].size();


        
	int minx=100000;
	int miny=100000;
	int maxx=0;
	int maxy=0;
	
	for(int k=0; k<4; k++)
	{
	if(p[k].x<minx) minx=p[k].x;
	if(p[k].y<miny) miny=p[k].y;
	if(p[k].x>maxx) maxx=p[k].x;
	if(p[k].y>maxy) maxy=p[k].y;
	}
	Rect rect=Rect(minx,miny,maxx-minx+1,maxy-miny+1);
	Mat small=image(rect);
	char num[21];
	sprintf(num,"%d",j);
	imshow(num,small);
	
	polylines(image, &p, &n, 1, true, Scalar(255,0,0), 3, LINE_AA);
	

    }

    imshow(wndname, image);


}


int main(int /*argc*/, char** /*argv*/)
{
	namedWindow( wndname, 1 );
    vector<vector<Point> > squares;
        Mat image = imread("image30.jpg", 1);
        if( image.empty() )
        {
            cout << "Couldn't load " << endl;

        }
	transpose(image,image);
	flip(image,image,1);
	resize(image,image,Size(image.cols/2,image.rows/2));

        findSquares(image, squares);
	squares=selectSquares(squares);
        drawSquares(image, squares);

        int c = waitKey();
        if( (char)c == 27 )
            return 1;
    

    return 0;
}