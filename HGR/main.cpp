#include <iostream>
#include <thread>
#include <mutex>

#include "hgrsvm.h"
#include "windows.h"
#include "../Drone/ardrone_testing_tool.h"

using namespace std;
using namespace cv;

mutex mtx;

void print_block (int n, char c) {
  // critical section (exclusive access to std::cout signaled by lifetime of lck):
  std::unique_lock<std::mutex> lck (mtx);
  (void)lck;
  for (int i=0; i<n; ++i) { std::cout << c; }
  std::cout << '\n';
}

int main(int argc, char *argv[])
{
    thread th1 (runArdrone,argc,argv);

    //runArdrone(argc, argv);

    //pour apprendre : lancer win.runLearn(), puis svm.train()

    HGRSVM svm;
    svm.train(10,1500,100);
    Windows win;
    win.runPredict(svm, "model.txt");

    th1.join();
    //th2.join();

    return 0;
}

