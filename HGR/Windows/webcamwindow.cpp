#include "webcamwindow.h"

extern int order;

WebcamWindow::WebcamWindow( string model )
    : AbstractWindow ( model )
{
    capture.open(0);
    context = new WindowContext( this );
}

void WebcamWindow::run() {

    ihm = true;

    while( ihm ) {
        capture.read( cameraFeed );
        context->execute( cameraFeed );
    }
    order = 0;
}
