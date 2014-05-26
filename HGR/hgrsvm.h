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
#include <dirent.h>
#include <regex>
#include <cmath>


using namespace std;
using namespace cv;

class HGRSVM
{
private :
    int totalLine;
public:
    HGRSVM();

    void fillTab (string pathFile, float label, float trainingData[][100], float labels[] );
    void train(int nbRegion );

    float HGRPredict(CvSVM &cvSvm, string line, int nbRegionByLine) ;

    void loadLabels(string resourcesPath , float trainingData[][100], float labels[]);

    vector<string> &split(const string &s, char delim, vector<string> &elems);
    vector<std::string> split(const std::string &s, char delim);

    int getNbFrame( string resourcesPath );

     ~HGRSVM();

};

#endif // HGRSVM_H
