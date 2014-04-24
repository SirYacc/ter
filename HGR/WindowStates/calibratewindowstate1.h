#ifndef CALIBRATEWINDOWSTATE1_H
#define CALIBRATEWINDOWSTATE1_H

#include "abstractwindowstate.h"
#include "frames.h"
#include "opencv/cv.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "my_roi.h"
#include <vector>
#include "binarywindowstate.h"

using namespace cv;
using namespace std;

class WindowContext;

class CalibrateWindowState1 : public AbstractWindowState
{
private:
    Frames &frames;
    Mat blackSq;
    Vector <My_ROI> roi;
    int square_len;
    int NSAMPLES;
    int avgColor[6][3];

public:
    CalibrateWindowState1(Mat cameraFeed, Frames & frames);

    virtual void execute( WindowContext &context, Mat &cameraFeed );

private:
    void setROI(Mat cameraFeed );
    int getMedian( vector< int > val );
    void getAvgColor( Mat m, My_ROI roi, int avg[3] );
    void minMaxValuesOfYCrCb( int min[3], int max[3] );
    void calibrate( Mat cameraFeed );
};

#endif // CALIBRATEWINDOWSTATE1_H
