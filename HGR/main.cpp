#include <iostream>
#include <thread>
#include <QMainWindow>
#include <QStackedWidget>
#include <QApplication>

#include "hgrsvm.h"
#include "Windows/mymainwindow.h"
#include "../Drone/ardrone_testing_tool.h"

using namespace std;
using namespace cv;

int order = -1;
IplImage *imgFromKarmen;

int main( int argc, char *argv[] )
{
    QApplication a( argc, argv );

    QMainWindow mainWindow;

    HGRSVM svm;
    svm.train( 100 );

    QStackedWidget *stackedWidget = new QStackedWidget;

    MyMainWindow *myMainWindow = new MyMainWindow( stackedWidget );

    stackedWidget->addWidget( myMainWindow );
    stackedWidget->setCurrentWidget( myMainWindow );

    mainWindow.setCentralWidget(stackedWidget);
    mainWindow.setWindowTitle( "Hand gesture recognition for ArDrone" );
    mainWindow.resize(950, 500);
    mainWindow.show();

    thread th1( runArdrone, argc, argv );

    int status = a.exec();

    order = 1;

    th1.join();

    return status;
}
