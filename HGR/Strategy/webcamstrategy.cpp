#include "webcamstrategy.h"

WebcamStrategy::WebcamStrategy()
    : VideoStreamStrategy()
{
    capture.open(0);
}

void WebcamStrategy::waitForVideoStream() {
    Mat cameraFeed;
    int cptLoop = 0;

    waitFor = true;

    capture.read( cameraFeed );

    while( cameraFeed.dims == 0 && waitFor ){
        capture.read( cameraFeed );

        if(cptLoop == 0){
            cout << " Waiting for image from webcam ..." << endl;
            cptLoop = 90;
        }
        else
            cptLoop --;

        waitKey(0);
    }
}

void WebcamStrategy::stopWaitForVideoStream() {
    waitFor = false;
}

void WebcamStrategy::read( Mat &cameraFeed ) {
    capture.read( cameraFeed );
}
