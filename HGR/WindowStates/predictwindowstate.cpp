#include "predictwindowstate.h"
#include "windowcontext.h"
#include "Windows/mywindow.h"

PredictWindowState::PredictWindowState( string modelSVM, Frames &frames )
    : frames( frames )
{
    nbRegionByLine = 10;
    cvSvm.load( modelSVM.c_str() );
}

void PredictWindowState::execute(WindowContext &context , Mat &cameraFeed) {

    skinMat  = frames.getSkin( cameraFeed );
    fullHand = frames.getFullHand( skinMat );

    context.getWindow()->setMainMat( skinMat );
    context.getWindow()->setSecondaryMat( fullHand );
    context.getWindow()->setInfoLabel();
    context.getWindow()->show();

    line = frames.getFormatedSVM( fullHand, nbRegionByLine );

    order = (int)hgrsvm.HGRPredict( cvSvm, line, nbRegionByLine );
    cout << "Thumb  : " << order << endl;
    newOrder = true;

    waitKey(0);
}
