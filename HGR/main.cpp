#include <iostream>
#include"hgrsvm.h"
#include "windows.h"
using namespace std;
using namespace cv;

int main()
{
    //pour apprendre : lancer win.runLearn(), puis svm.train()

    HGRSVM svm;
    svm.train(10,1500,100);
    Windows win;
    win.runPredict(svm, "model.txt");

    return 0;
}

