#include "dronewindow.h"

extern int order;
extern IplImage *imgFromKarmen;

DroneWindow::DroneWindow( string model )
    : AbstractWindow( model )
{
    context = new WindowContext( this );

    blackCameraFeed = Mat::zeros( Size(600,480), CV_8UC1 );
    blackSq = Mat::zeros( Size(300,300), CV_8UC1 );
}

void DroneWindow::run() {

    ihm = true;

    waitForDroneVideoStream( );

    while( ihm ) {
        cameraFeed = Mat( imgFromKarmen );
        context->execute( cameraFeed );
    }
    order = 0;
}

void DroneWindow::waitForDroneVideoStream( void ) {

    inWaitForDroneVideoStream( true );

    int cptLoop = 0;

    setMainMat( blackCameraFeed );
    setSecondaryMat( blackSq );

    cameraFeed = Mat( imgFromKarmen );

    while( cameraFeed.dims == 0 && ihm ){
        cameraFeed = Mat( imgFromKarmen );

        if(cptLoop == 0){
            cout << " En attente du drone ..." << endl;
            cptLoop = 90;
        }
        else
            cptLoop --;

        waitKey(0);
    }

    inWaitForDroneVideoStream( false );
}

void DroneWindow::inWaitForDroneVideoStream( bool mode ) {
    buttonRP->setDisabled( mode );
    buttonRL->setDisabled( mode );
    buttonC->setDisabled( mode );
    buttonLand->setDisabled( mode );
}
