#ifndef BINARYWINDOWSTATE_H
#define BINARYWINDOWSTATE_H

#include "abstractwindowstate.h"
#include "frames.h"
#include "opencv/cv.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

class WindowContext;

class BinaryWindowState : public AbstractWindowState
{
private:
    Mat skinMat;
    Mat blackSq;
    Frames &frames;

public:
    BinaryWindowState(Frames &frames);

    virtual void execute( WindowContext &context, Mat &cameraFeed );
};

#endif // BINARYWINDOWSTATE_H
