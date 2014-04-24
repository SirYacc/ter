#include "predictwindowstate.h"
#include "windowcontext.h"
#include "Windows/abstractwindow.h"

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
    context.getWindow()->show();

    line = frames.getFormatedSVM( fullHand, nbRegionByLine );

    order = (int)hgrsvm.createPredictedData( cvSvm, line, nbRegionByLine );
    cout << "Thumb  : " << order << endl;

    waitKey(0);
}
