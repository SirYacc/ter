#include "defaultwindowstate.h"
#include "windowcontext.h"
#include "Windows/mywindow.h"

DefaultWindowState::DefaultWindowState( void )
    : AbstractWindowState ()
{
    blackSq = Mat::zeros( Size(300,300), CV_8UC1 );
}

void DefaultWindowState::execute(WindowContext &context , Mat &cameraFeed) {

    context.getWindow()->setMainMat( cameraFeed );
    context.getWindow()->setSecondaryMat( blackSq );
    context.getWindow()->setInfoLabel();
    context.getWindow()->show();

    waitKey(10);
}
