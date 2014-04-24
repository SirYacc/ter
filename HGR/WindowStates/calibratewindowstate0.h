#ifndef CALIBRATEWINDOWSTATE0_H
#define CALIBRATEWINDOWSTATE0_H

#include "abstractwindowstate.h"
#include "opencv/cv.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "my_roi.h"

using namespace cv;

class WindowContext;

class CalibrateWindowState0 : public AbstractWindowState
{
private:
    Mat blackSq;
    Vector <My_ROI> roi;
    int square_len;
    int NSAMPLES;

public:
    CalibrateWindowState0(Mat cameraFeed );

    virtual void execute( WindowContext &context, Mat &cameraFeed );

private:
    void setROI( Mat cameraFeed );
};

#endif // CALIBRATEWINDOWSTATE_H
