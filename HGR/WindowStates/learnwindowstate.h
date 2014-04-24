#ifndef LEARNWINDOWSTATE_H
#define LEARNWINDOWSTATE_H

#include "abstractwindowstate.h"
#include "opencv/cv.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <fstream>
#include "frames.h"

using namespace cv;
using namespace std;

class WindowContext;

class LearnWindowState : public AbstractWindowState
{
private:
    Mat skinMat;
    Mat fullHand;

    ofstream file;
    Frames frames;

    int nbRegionByLine;
    int cptFrames;
    int nbImg;
    int starter;

public:
    LearnWindowState(string filePath, Frames frames);
    ~LearnWindowState();

    virtual void execute( WindowContext &context, Mat &cameraFeed );
};

#endif // LEARNWINDOWSTATE_H
