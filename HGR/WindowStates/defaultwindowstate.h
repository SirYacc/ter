#ifndef DEFAULTWINDOWSTATE_H
#define DEFAULTWINDOWSTATE_H

#include "abstractwindowstate.h"
#include "opencv/cv.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

class WindowContext;

class DefaultWindowState : public AbstractWindowState
{
private:
    Mat cameraFeed;
    Mat blackSq;

public:
    DefaultWindowState( void );

    virtual void execute( WindowContext &context, Mat &cameraFeed );
};

#endif // DEFAULTWINDOWSTATE_H
