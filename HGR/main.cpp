#include <iostream>
#include <thread>
#include <mutex>
#include "hgrsvm.h"
#include "windows.h"
#include "../Drone/ardrone_testing_tool.h"

using namespace std;
using namespace cv;

mutex mtx;
int order = -1;
IplImage *imgFromKarmen;

void print_block (int n, char c) {
    // critical section (exclusive access to std::cout signaled by lifetime of lck):
    std::unique_lock<std::mutex> lck (mtx);
    (void)lck;
    for (int i=0; i<n; ++i) { std::cout << c; }
    std::cout << '\n';
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    //MainWindow w;

    //pour apprendre : lancer win.runLearn(), puis svm.train()

    HGRSVM svm;
    svm.train( 100 );
    Windows *win = new Windows(argc, argv,svm,"model.txt");
//    w.setCentralWidget(win);
//    w.show();
    thread th1( runArdrone, argc, argv );

  // win->runPredictC();
   win->runDefault();
   th1.join();

    return a.exec();
}
