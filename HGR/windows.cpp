#include "windows.h"

using namespace std;
using namespace cv;

extern int order;
extern IplImage *imgFromKarmen;

Windows::Windows()
{
}

int Windows::runLearn(string filePath){
    ofstream file(filePath.c_str(), ios::out | ios::trunc);

    if(!file){
        cerr << "Impossible d'ouvrir le fichier !" << endl;
        exit(0);
    }

    VideoCapture capture;
    capture.open(0);

    //set height and width of capture frame
    capture.set(CV_CAP_PROP_FRAME_WIDTH,320);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT,480);

    Mat cameraFeed;
    Mat skinMat;
    Mat fullHand;

    int nbRegionByLine = 10;
    int cptFrames = 0;
    int nbImg = 0;
    int starter = 0;


    while(1){

        //store image to matrix
        capture.read(cameraFeed);

        //show the current image
        imshow("Original Image",cameraFeed);

        skinMat= frames.getSkin(cameraFeed);

        // Creation des .txt
        //on prend une photo toute les 10 frames

        fullHand = frames.getFullHand(skinMat);

        if(starter >= 100){
            if(cptFrames == 10){
                file  << frames.getFormatedSVM(fullHand,nbRegionByLine) << endl;
                cptFrames = 0;
                cout << nbImg++ << endl;
            }
            else cptFrames++;
        }
        else cout << " " <<starter ++;


        imshow("Full hand",fullHand);
        imshow("Skin Image",skinMat);

        int c = waitKey(10);
        if( (char)c == 'c' || nbImg >= 300)
            break;
    }
    file.close();
    return 0;
}


int Windows::runPredictD(HGRSVM svm, string file){

    VideoCapture capture;
    //open capture object at location zero (default location for webcam)

    capture.open(0);

    //set height and width of capture frame
    capture.set(CV_CAP_PROP_FRAME_WIDTH,320);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT,480);

    Mat cameraFeed;

    Mat karmenMat = Mat(imgFromKarmen);

    Mat skinMat;
    Mat fullHand;

    int nbRegionByLine = 10;
    string line;
    CvSVM cvSvm;
    cvSvm.load(file.c_str());

    string fullHandImg = "Full hand";
    namedWindow( fullHandImg, CV_WINDOW_AUTOSIZE );
    moveWindow(fullHandImg,1200,200);

    string skinImg = "Skin Image";
    namedWindow( skinImg, CV_WINDOW_AUTOSIZE );
    moveWindow(skinImg,500,200);

    int cptLoop = 0;
    while(karmenMat.dims == 0){
        karmenMat = Mat(imgFromKarmen);
        if(cptLoop == 0){
            cout << " En attente du drone ..." << endl;
            cptLoop = 900000000;
        }
        else cptLoop --;

    }

    while(1){

        karmenMat = Mat(imgFromKarmen);

        //store image to matrix
        // capture.read(cameraFeed);

        //show the current image
        //imshow("Original Image",cameraFeed);

        skinMat= frames.getSkin(karmenMat);
        fullHand = frames.getFullHand(skinMat);

        line = frames.getFormatedSVM( fullHand, nbRegionByLine );

        // dataMat = svm.createPredictedData( line, nbRegionByLine );


        // cout << "Thumb  : " << cvSvm.predict( dataMat ) << endl;
        order = (int)svm.createPredictedData( line, nbRegionByLine );
        //cout << "Thumb  : " << order << endl;



        imshow(fullHandImg , fullHand);
        imshow(skinImg , skinMat);



        int c = waitKey(10);
        if( (char)c == 'c') {
            order = 1; // Land
            break;
        }
    }
    return 0;
}


int Windows::runPredictC(HGRSVM svm, string file){

    VideoCapture capture;
    //open capture object at location zero (default location for webcam)

    capture.open(0);

    //set height and width of capture frame
    capture.set(CV_CAP_PROP_FRAME_WIDTH,320);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT,480);

    Mat cameraFeed;

    Mat skinMat;
    Mat fullHand;

    int nbRegionByLine = 10;
    string line;
    CvSVM cvSvm;
    cvSvm.load(file.c_str());

    string fullHandImg = "Full hand";
    namedWindow( fullHandImg, CV_WINDOW_AUTOSIZE );
    moveWindow(fullHandImg,1200,200);

    string skinImg = "Skin Image";
    namedWindow( skinImg, CV_WINDOW_AUTOSIZE );
    moveWindow(skinImg,500,200);



    while(1){

        //store image to matrix
        capture.read(cameraFeed);

        //show the current image
        //imshow("Original Image",cameraFeed);

        skinMat= frames.getSkin(cameraFeed);
        fullHand = frames.getFullHand(skinMat);

        line = frames.getFormatedSVM( fullHand, nbRegionByLine );

        // dataMat = svm.createPredictedData( line, nbRegionByLine );


        // cout << "Thumb  : " << cvSvm.predict( dataMat ) << endl;
        order = (int)svm.createPredictedData( line, nbRegionByLine );
        //cout << "Thumb  : " << order << endl;



        imshow(fullHandImg , fullHand);
        imshow(skinImg , skinMat);



        int c = waitKey(10);
        if( (char)c == 'c') {
            order = 1; // Land
            break;
        }
    }
    return 0;
}


Windows::~Windows(){

}
