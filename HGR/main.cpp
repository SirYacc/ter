#include <iostream>
#include <thread>
#include <QMainWindow>
#include <QStackedWidget>
#include <QApplication>
#include "cvdrone/src/ardrone/ardrone.h"
#include "hgrsvm.h"
#include "Windows/mymainwindow.h"

int runArdrone();
using namespace std;
using namespace cv;

int order = -1;
IplImage *imgFromKarmen;
bool newOrder = false;
int battery = 0;
QString orderName;

int main( int argc, char *argv[] )
{

    QApplication a( argc, argv );

    QMainWindow mainWindow;

    HGRSVM svm = HGRSVM();
    svm.train( 100 );

    QStackedWidget *stackedWidget = new QStackedWidget;

    MyMainWindow *myMainWindow = new MyMainWindow( stackedWidget );

    stackedWidget->addWidget( myMainWindow );
    stackedWidget->setCurrentWidget( myMainWindow );

    mainWindow.setCentralWidget(stackedWidget);
    mainWindow.setWindowTitle( "Hand gesture recognition for ArDrone" );
    mainWindow.resize(950, 500);
    mainWindow.show();

    thread th1( runArdrone );


    int status = a.exec();



    order = 1;
 th1.join();

    return status;
}
