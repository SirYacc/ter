#ifndef VIDEOSTREAMSTRATEGY_H
#define VIDEOSTREAMSTRATEGY_H

#include "opencv/cv.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

class VideoStreamStrategy
{
public:
    VideoStreamStrategy();

    virtual void waitForVideoStream() = 0;
    virtual void stopWaitForVideoStream() = 0;
    virtual void read( Mat &cameraFeed ) = 0;
};

#endif // VIDEOSTREAMSTRATEGY_H
