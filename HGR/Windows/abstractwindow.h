#ifndef ABSTRACTWINDOW_H
#define ABSTRACTWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include "opencv/cv.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "windowcontext.h"
#include "frames.h"

#include "WindowStates/predictwindowstate.h"
#include "WindowStates/calibratewindowstate0.h"
#include "WindowStates/calibratewindowstate1.h"
#include "WindowStates/learnwindowstate.h"
#include "WindowStates/defaultwindowstate.h"

using namespace cv;

class AbstractWindow : public QWidget
{
    Q_OBJECT
protected:
    WindowContext *context;
    Frames frames;

    string model;
    bool ihm;

    Mat _mainMat;
    Mat _secondaryMat;
    Mat cameraFeed;

    QLabel* _mainLabel;
    QLabel* _secondaryLabel;
    QPushButton* buttonRP;
    QPushButton* buttonRL;
    QPushButton* buttonC;
    QPushButton* buttonLand;
    QPushButton* buttonCam;

public:
    AbstractWindow( string model, QWidget *parent = 0 );

    void setMainMat(const Mat &newmat);
    void setSecondaryMat(const Mat &newmat);
    void inFlightMode( bool mode );
    void inCalibrateMode( bool mode );

    virtual void run() = 0;

protected:
    void setMainLabel();
    void setSecondaryLabel();

protected slots:
    void setModeP();
    void setModeC0();
    void setModeC1();
    void setModeL();
    void setLanding();
    void onChangeCameraFeedClicked();
};

#endif // ABSTRACTWINDOW_H
