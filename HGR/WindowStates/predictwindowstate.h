#ifndef PREDICTWINDOWSTATE_H
#define PREDICTWINDOWSTATE_H

#include "abstractwindowstate.h"
#include "opencv/cv.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "frames.h"
#include "hgrsvm.h"

extern int order;
extern bool newOrder;

using namespace cv;

class WindowContext;

class PredictWindowState : public AbstractWindowState
{
private:
    Mat cameraFeed;
    Mat skinMat;
    Mat fullHand;
    string line;
    CvSVM cvSvm;
    int nbRegionByLine;
    Frames &frames;
    HGRSVM hgrsvm;

public:
    PredictWindowState(string modelSVM , Frames &frames);

    virtual void execute( WindowContext &context, Mat &cameraFeed );
};

#endif // WEBCAMWINDOWSTATE_H
