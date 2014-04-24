#ifndef DRONEWINDOW_H
#define DRONEWINDOW_H

#include "abstractwindow.h"

using namespace cv;
using namespace std;

class DroneWindow : public AbstractWindow
{
private:
    Mat blackSq;
    Mat blackCameraFeed;

public:
    DroneWindow( string model );

    virtual void run();

private:
    void waitForDroneVideoStream( void );
    void inWaitForDroneVideoStream( bool mode );
};

#endif // DRONEWINDOW_H
