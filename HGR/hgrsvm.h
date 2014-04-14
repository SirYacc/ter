#ifndef HGRSVM_H
#define HGRSVM_H
#include"opencv/cv.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <fstream>


using namespace std;
using namespace cv;

class HGRSVM
{
private :
public:
    HGRSVM();

    void fillTab ( int nb, string pathFile, float label, float trainingData[][100], float labels[] );
    void train( int nbRegionByLine, int nbFrame, int nbRegion );

    float createPredictedData( string line, int nbRegionByLine) ;

     ~HGRSVM();

};

#endif // HGRSVM_H
