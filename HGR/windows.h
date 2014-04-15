#ifndef WINDOWS_H
#define WINDOWS_H
#include"opencv/cv.h"
#include "frames.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <fstream>
#include "hgrsvm.h"

using namespace std;
using namespace cv;

class Windows
{
private:
    Frames frames;
    CvSVM cvSvm;
public:
    Windows();
    int runLearn(string filePath);
    int runPredictD(HGRSVM svm, string file);
    int runPredictC(HGRSVM svm, string file);

    ~Windows();

};

#endif // WINDOWS_H
