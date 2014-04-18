#ifndef WINDOWS_H
#define WINDOWS_H
#include <QApplication>
#include <QtGui>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
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
#include "my_roi.h"

using namespace std;
using namespace cv;

class Windows : public QWidget
{

    Q_OBJECT
private:
    Frames frames;
    CvSVM cvSvm;
    int mode;
    HGRSVM hgrsvm;
    string model;

    Mat _mainMat;
    Mat _secondaryMat;
    QLabel* _mainLabel;
    QLabel* _secondaryLabel;
    QPushButton* buttonRPC;
    QPushButton* buttonRPD;
    QPushButton* buttonRL;
    QPushButton* buttonC;
    QPushButton* buttonLand;
    VideoCapture capture;

    Vector <My_ROI> roi;
    int square_len;
    int NSAMPLES;
    int avgColor[6][3];
    //QApplication a;


    void setMainLabel();
    void setSecondaryLabel();

public:
    Windows(int argc, char *argv[], HGRSVM svm, string file, QWidget *parent = 0);
    Windows(QWidget *parent = 0);
    ~Windows();

    void runDefault();
    int runLearn(string filePath);
    int runPredictD();
    void runPredictC();

    void setMainMat(const Mat &newmat);
    void setSecondaryMat(const Mat &newmat);

    void changeRunMode();
    void average();

    void minMaxValuesOfYCrCb( int min[3], int max[3] );
    void calibrate( );
    void runCalibrate();
    void waitForPalmCover();
    int getMedian(vector<int> val);
    void getAvgColor( Mat m, My_ROI roi, int avg[3]);


private slots:
    void setModePC();
    void setModePD();
    void setModeC();
    void setModeL();
    void setLanding();


};

#endif // WINDOWS_H
