#include "dronestrategy.h"

DroneStrategy::DroneStrategy()
    : VideoStreamStrategy()
{
}

void DroneStrategy::waitForVideoStream() {

    Mat cameraFeed;
    int cptLoop = 0;

    waitFor = true;

    cameraFeed = Mat( imgFromKarmen );

    while( cameraFeed.dims == 0 && waitFor ){
        cameraFeed = Mat( imgFromKarmen );

        if(cptLoop == 0){
            cout << " Waiting for image from drone ..." << endl;
            cptLoop = 90;
        }
        else
            cptLoop --;

        waitKey(0);
    }
}

void DroneStrategy::stopWaitForVideoStream() {
    waitFor = false;
}

void DroneStrategy::read( Mat &cameraFeed ) {
    IplImage save = *imgFromKarmen;
    cameraFeed = Mat( &save );
}
