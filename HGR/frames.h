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

    inline void getYCbCr(int *tab){
        tab[0] = Y_MIN;
        tab[1] = Y_MAX;
        tab[2] = Cr_MIN;
        tab[3] = Cr_MAX;
        tab[4] = Cb_MIN;
        tab[5] = Cb_MAX;
    }

    inline void setYMin(int v){
        Y_MIN = v;
    }

    inline void setYMax(int v){
        Y_MAX = v;
    }

    inline void setCrMin(int v){
        Cr_MIN = v;
    }

    inline void setCrMax(int v){
        Cr_MAX = v;
    }

    inline void setCbMin(int v){
        Cb_MIN = v;
    }

    inline void setCbMax(int v){
        Cb_MAX = v;
    }

    inline int getYMin(){
        return Y_MIN;
    }

    inline int getYMax(){
        return Y_MAX;
    }

    inline int getCrMin(){
        return Cr_MIN;
    }

    inline int getCrMax(){
        return Cr_MAX;
    }

    inline int getCbMin(){
        return Cb_MIN;
    }

    inline int getCbMax(){
        return Cb_MAX;
    }

    ~Frames();
};

#endif // FRAME_H
