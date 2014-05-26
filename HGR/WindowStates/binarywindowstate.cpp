#include "binarywindowstate.h"
#include "windowcontext.h"
#include "Windows/mywindow.h"

BinaryWindowState::BinaryWindowState( Frames &frames )
    : blackSq( Mat::zeros( Size( 300, 300 ), CV_8UC1 )),
      frames( frames )
{
}

void BinaryWindowState::execute( WindowContext &context, Mat &cameraFeed ) {

    skinMat = frames.getSkin( cameraFeed );

    context.getWindow()->setMainMat( skinMat );
    context.getWindow()->setSecondaryMat( blackSq );
    context.getWindow()->setInfoLabel();
    context.getWindow()->show();

    waitKey( 0 );
}

