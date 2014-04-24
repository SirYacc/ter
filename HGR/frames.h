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
public:
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

    inline void setYCrCbMin(int Y, int Cr, int Cb){
        if(Cr < 0)
            Cr = 0;
        if(Cr > 255)
            Cr = 255;
        if(Cb < 0)
            Cb = 0;
        if(Cb > 255)
            Cb = 255;

        Y_MIN = Y;
        Cr_MIN = Cr;
        Cb_MIN = Cb;

        //cout << Y << " " << Cr << " " << Cb << endl;
    }

    inline void setYCrCbMax(int Y, int Cr, int Cb){

        if(Cr < 0)
            Cr = 0;
        if(Cr > 255)
            Cr = 255;
        if(Cb < 0)
            Cb = 0;
        if(Cb > 255)
            Cb = 255;

        Y_MAX = Y;
        Cr_MAX = Cr;
        Cb_MAX = Cb;

        //cout << Y << " " << Cr << " " << Cb << endl;
    }


    ~Frames();
};

#endif // FRAME_H
