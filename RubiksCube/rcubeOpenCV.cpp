
#include "rcubeOpenCV.hpp"

#define HRES 640
#define VRES 480

int thresh = 50, N = 11;
const char* rubiksDetect = "Rubik's Detection";
const char* internalCube = "Internal Model";

const char* const stateDesc[] =
{
    "Turn White face to camera with Blue face upward",
    "Turn Yellow face to camera with Green face upward",
    "Turn Green face to camera with White face upward",
    "Turn Blue face to camera with White face upward",
    "Turn Red face to camera with White face upward",
    "Turn Orange face to camera with White face upward",
    "Done!"
};

using namespace cv;
using namespace std;

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

bool pointSortY(Point2f a, Point2f b)
{
  return a.y < b.y;
}

bool pointSortX(Point2f a, Point2f b)
{
  return a.x < b.x;
}

static vector<Scalar> getSquareAvgColors(vector<Point2f>& centers, const Mat& image)
{
  // Container for colors
  vector<Scalar> colors(centers.size());
  
  for (size_t i = 0; i < centers.size(); ++i)
  {
    int xCenter = round(centers[i].x);
    int yCenter = round(centers[i].y);
    int h, s, v;
    h = s = v = 0;
    
    // Get average of the 3x3 block at center of contour
    for(int j = 0; j < 3; j++)
    {
      for(int k = 0; k < 3; k++)
      {
        cv::Vec3b hsv = image.at<cv::Vec3b>(yCenter - 1 + j, xCenter - 1 + k);
        h += (int)hsv[0]; // H Value
        s += (int)hsv[1]; // S Value
        v += (int)hsv[2]; // V Value
      }
    }
    
    // Average
    Scalar avgColor(round(h/9), round(s/9), round(v/9));
    colors[i] = avgColor;
    
    #ifdef DEBUG
    std::cout << avgColor << std::endl;
    #endif
  }
  return colors;
}

static vector<Point2f> getSortedCenters(vector<vector<Point> >& squares)
{
  /// Get the moments
  vector<Moments> mu(squares.size() );
  for( int i = 0; i < (int)squares.size(); i++ )
    { mu[i] = moments( squares[i], false ); }

  ///  Get the mass centers:
  vector<Point2f> mc( squares.size() );
  for( int i = 0; i < (int)squares.size(); i++ )
    { mc[i] = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 ); }
  
  stable_sort(mc.begin(), mc.end(), pointSortY);
  stable_sort(mc.begin(), mc.end() - 6, pointSortX);
  stable_sort(mc.begin() + 3, mc.end() - 3, pointSortX);
  stable_sort(mc.begin() + 6, mc.end(), pointSortX);
  
  #ifdef DEBUG
  for(int i =0; i < (int)mc.size(); i++)
  {
    std::cout << mc[i] << std::endl;
  }
  #endif
  return mc;
}

// Filter the squares to our needs
static void filterSquares(vector< vector<Point> >& squares)
{
  #ifdef DEBUG
  std::cout << "Filtering Squares. Size: " << squares.size() << std::endl;
  #endif
  if(squares.size() < 9)
  {
    // we need at least 9
    squares.clear();
  }
  else
  {
    // Filter
    double sensitivity0 = 35; // in pixels
    double sensitivity1 = 1.05; // in (1+%)
    
    /// Get the moments
    vector<Moments> mu(squares.size() );
    for( int i = 0; i < (int)squares.size(); i++ )
      { mu[i] = moments( squares[i], false ); }

    ///  Get the mass centers:
    vector<Point2f> mc( squares.size() );
    for( int i = 0; i < (int)squares.size(); i++ )
      { mc[i] = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 ); } 
    
    vector<double> m0;    // Area of square

    
    // Filter approx. repeats
    for(int i = 0; i < (int)squares.size(); i++)
    {      
      for(int j = i + 1; j < (int)squares.size(); j++)
      {
        // Check for all
        if(((mc[i].x + sensitivity0) > mc[j].x &&
            (mc[i].x - sensitivity0) < mc[j].x) &&
           ((mc[i].y + sensitivity0) > mc[j].y &&
            (mc[i].y - sensitivity0) < mc[j].y))
        {
          #ifdef DEBUG
          std::cout << "Point 1: " << mc[i] << std::endl;
          std::cout << "Point 2: " << mc[j] << std::endl;
          #endif
          // remove it
          squares.erase(squares.begin() + j);
          mu.erase(mu.begin() + j);
          mc.erase(mc.begin() + j);
          j--;
        }
      }
    }
    
    
    for(int i = 0; i < (int)squares.size(); i++)
    {
      #ifdef DEBUG
      std::cout << "Point " << i << ": " << mc[i] << std::endl;
      #endif
      m0.push_back(mu[i].m00); // needs to be in separate vector for sorting
    }
    // sort contour squares based off area
    qsortMirror(m0, squares, 0, squares.size() - 1);
    for(int i = 0; i < (int)squares.size() - 1; i++)
    {
      if(m0[i]*(sensitivity1) < m0[i + 1])
      {
        m0.erase(m0.begin() + i);
        squares.erase(squares.begin() + i);
        i--;
      }
    }
  }
  
  #ifdef DEBUG
  std::cout << "Filtering Done. Size: " << squares.size() << std::endl;
  #endif
}

// the function draws all the squares in the image
static void drawSquares( Mat& image, const vector<vector<Point> >& squares )
{
  for( size_t i = 0; i < squares.size(); i++ )
  {
    const Point* p = &squares[i][0];
    int n = (int)squares[i].size();
    if((*p).x > 10 && (*p).y > 10)// Edge of screen
    {
      polylines(image, &p, &n, 1, true, Scalar(0,255,0), 3, LINE_AA);
    }
  }

  imshow(rubiksDetect, image);
}

static rcolor_t cvtHSV2RColor(Scalar hsv)
{
    if(hsv[1] >= 86 && hsv[2] >= 70)
    {
        if((hsv[0] >= 0 && hsv[0] <= 9) || (hsv[0] >= 151 && hsv[0] <= 180))
        {
            return RED;
        }
        else if(hsv[0] >= 10 && hsv[0] <= 15)
        {
            return ORANGE;
        }
        else if(hsv[0] >= 16 && hsv[0] <= 45)
        {
            return YELLOW;
        }
        else if(hsv[0] >= 46 && hsv[0] <= 89)
        {
            return GREEN;
        }
        else if(hsv[0] >= 90 && hsv[0] <= 150)
        {
            return BLUE;
        }
        else
        {
            std::cout << "Unknown HSV Value" << std::endl;
            return (rcolor_t)-1;
        }
    }
	else if((hsv[1] >= 0 && hsv[1] <= 85) && (hsv[2] >= 128 && hsv[2] <= 255))
	{
        return WHITE;
    }
    else
    {
        std::cout << "Unknown HSV Value: " << hsv << std::endl;
        return (rcolor_t)-1;
    }
}

static bool assignFace(int state, vector<Scalar> hsv, RCube& rubiks)
{
    vector<rcolor_t> colors(hsv.size());
    for(int i = 0; i < (int)hsv.size(); i++)
    {
        colors[i]  = cvtHSV2RColor(hsv[i]);
    }
    
    // Refer to sticker.hpp for color-state numbers
    // Check center
    if(colors[4] != (rcolor_t)state)
    {
        std::cout << "Error: Incorrect Face!" << std::endl;
        return false;
    }
    else
    {
        // Assign values, refer to rface.hpp for positioning
        for(int i = 0; i < (int)colors.size(); i++)
        {
            if((int)colors[i] != -1)
            {
                rubiks.SetStickerColor(colors[4], colors[i], (rposition_t)i);
            }
            else
                return false;
        }
        return true;
    }
}

// Actually assign things
bool assignRCubeCV(RCube& rubiks)
{
    CvCapture* capture;
    int dev=0;
	IplImage* frame;
	int frameV = VRES, frameH = HRES;
    bool done = false;
    int state = 0;
    Mat cubeMat(STICKER_SIZE*(9 + 3), STICKER_SIZE*(12+3), CV_8UC3);
    cubeMat.setTo(Scalar(255,255,255));
    
    namedWindow( rubiksDetect, CV_WINDOW_AUTOSIZE );
    namedWindow( internalCube, CV_WINDOW_AUTOSIZE );
    vector<vector<Point> > squares;

	capture = (CvCapture *)cvCreateCameraCapture(dev);
    cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, frameH);
    cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, frameV);
	
	
    while(!done)
    {
        // Transformation ================================================

        frame=cvQueryFrame(capture);

        Mat mat_img(cvarrToMat(frame));

        // Do Work
        findSquares(mat_img, squares);
        filterSquares(squares);
        if(squares.size() == 9 && state < 6)
        {
            // Get Colors
            Mat hsv_mat;
            cvtColor(mat_img, hsv_mat, COLOR_BGR2HSV);

            vector<Point2f> centers = getSortedCenters(squares);
            vector<Scalar> hsvAvgs = getSquareAvgColors(centers, hsv_mat);
            
            // Assign things
            if(assignFace(state, hsvAvgs, rubiks))
            {
                state++;
            }
        }
        
        cubeMat << rubiks;
        cv::putText(cubeMat, stateDesc[state], cv::Point(STICKER_SIZE*1 - 3, STICKER_SIZE*(9+2) - 3), FONT_HERSHEY_SIMPLEX,
                    0.8, cvScalar(0,0,0), 1, CV_AA);
        drawSquares(mat_img, squares);
        imshow(internalCube, cubeMat);
        

        if(!frame) break;
        // ==================================================================

        char c = cvWaitKey(10);
        if( c == 27  || c == 'q') break;
        if( c == 'r' && state > 0)
        {
            // In case of bad read, reset
            state--;
            rubiks.ResetFace((rcolor_t)state);
        }
        else if(c == 'c')
        {
            destroyWindow(rubiksDetect);
            break;
        }
    }

    cvReleaseCapture(&capture);
    
    return true;
}
