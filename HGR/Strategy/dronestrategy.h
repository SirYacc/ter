#ifndef DRONESTRATEGY_H
#define DRONESTRATEGY_H

#include "videostreamstrategy.h"

using namespace cv;
using namespace std;

extern IplImage *imgFromKarmen;

class DroneStrategy : public VideoStreamStrategy
{
private:
    bool waitFor;

public:
    DroneStrategy();

    virtual void waitForVideoStream();
    virtual void stopWaitForVideoStream();
    virtual void read( Mat &cameraFeed );
};

#endif // DRONESTRATEGY_H
