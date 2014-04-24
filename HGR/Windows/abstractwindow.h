#ifndef ABSTRACTWINDOW_H
#define ABSTRACTWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSlider>
#include <QGroupBox>
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
    VideoCapture capture;

    QSlider *yMinSlider;
    QSlider *yMaxSlider;
    QSlider *CrMinSlider;
    QSlider *CrMaxSlider;
    QSlider *CbMinSlider;
    QSlider *CbMaxSlider;
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

    //TODO enlever le inline ?
    inline void setYMin(int v){
        if(frames.getYMax() >= v)
            frames.setYMin(v);
        else
            yMinSlider->setValue(frames.getYMin());
    }
    inline void setYMax(int v){
        if(frames.getYMin() <= v)
            frames.setYMax(v);
        else
            yMaxSlider->setValue(frames.getYMax());
    }
    inline void setCrMin(int v){
        if(frames.getCrMax() >= v)
           frames.setCrMin(v);
        else
            CrMinSlider->setValue(frames.getCrMin());
    }
    inline void setCrMax(int v){
        if(frames.getCrMin() <= v)
            frames.setCrMax(v);
        else
            CrMaxSlider->setValue(frames.getCrMax());
    }
    inline void setCbMin(int v){
        if(frames.getCbMax() >= v)
           frames.setCbMin(v);
        else
            CbMinSlider->setValue(frames.getCbMin());
    }
    inline void setCbMax(int v){
        if(frames.getCbMin() <= v)
            frames.setCbMax(v);
        else
            CbMaxSlider->setValue(frames.getCbMax());
    }
};

#endif // ABSTRACTWINDOW_H
