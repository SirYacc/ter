#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QPushButton>

#include "Strategy/videostreamstrategy.h"
#include "Strategy/webcamstrategy.h"
#include "Strategy/dronestrategy.h"
#include "mywindow.h"

class MyMainWindow : public QWidget
{
    Q_OBJECT
private:
    QStackedWidget *stackedWidget;

    QPushButton *droneButton;
    QPushButton *webcamButton;

    MyWindow *window;
    WebcamStrategy *webcamStrategy;
    DroneStrategy *droneStrategy;

public:
    MyMainWindow( QStackedWidget *stackedWidget, QWidget *parent = 0 );

private slots:
    void setModeDrone();
    void setModeWebcam();
};

#endif // MAINWINDOW_H
