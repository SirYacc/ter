#ifndef WEBCAMSTRATEGY_H
#define WEBCAMSTRATEGY_H

#include "videostreamstrategy.h"

using namespace cv;
using namespace std;

class WebcamStrategy : public VideoStreamStrategy
{
private:
    VideoCapture capture;
    bool waitFor;

public:
    WebcamStrategy();

    virtual void waitForVideoStream();
    virtual void stopWaitForVideoStream();
    virtual void read( Mat &cameraFeed );
};

#endif // WEBCAMSTRATEGY_H
