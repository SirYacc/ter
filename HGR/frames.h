#ifndef FRAME_H
#define FRAME_H
#include"opencv/cv.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <string>

using namespace cv;
using namespace std;

class Frames
{
private:
    int Y_MIN;
    int Y_MAX;
    int Cr_MIN;
    int Cr_MAX;
    int Cb_MIN;
    int Cb_MAX;

private:
    String convertToString( bool *tab, int size );

public:
    Frames( void );

    Mat getSkin( Mat input );

    int findBiggestContour( vector< vector< Point > > contours );

    Rect getBoundingRectOfBiggestContour(Mat input );

    void resizeRect( Rect *rect );

    Mat getFullHand(Mat input );

    Mat divideFrameIntoSquares( Mat frame, int gridWidthInPixel );

    String getFormatedSVM( Mat frame, int nbRegionByLine );

    void printTabOfRegion( bool *tab, int size, int nbCellByLine );

    ~Frames();
};

#endif // FRAME_H
