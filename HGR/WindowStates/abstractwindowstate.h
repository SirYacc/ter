#ifndef ABSTRACTWINDOWSTATE_H
#define ABSTRACTWINDOWSTATE_H

#include "opencv/cv.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

class WindowContext;

class AbstractWindowState
{
public:
    AbstractWindowState( void );

    virtual void execute( WindowContext &context, Mat &cameraFeed ) = 0;
};

#endif // ABSTRACTWINDOWSTATE_H
