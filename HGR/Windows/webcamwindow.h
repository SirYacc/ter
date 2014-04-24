#ifndef WEBCAMWINDOW_H
#define WEBCAMWINDOW_H

#include "abstractwindow.h"
#include "WindowStates/predictwindowstate.h"
#include "WindowStates/calibratewindowstate0.h"
#include "WindowStates/calibratewindowstate1.h"
#include "WindowStates/learnwindowstate.h"
#include "WindowStates/defaultwindowstate.h"

using namespace cv;
using namespace std;

class WebcamWindow : public AbstractWindow
{
private:
    VideoCapture capture;

public:
    WebcamWindow( string model );

    virtual void run();
};

#endif // WEBCAMWINDOW_H
