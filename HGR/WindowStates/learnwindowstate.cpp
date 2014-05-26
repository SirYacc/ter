#include "learnwindowstate.h"
#include "windowcontext.h"
#include "Windows/mywindow.h"

LearnWindowState::LearnWindowState( string filePath, Frames frames )
    : //file( filePath.c_str(), ios::out | ios::trunc ),
      frames( frames )
{
    nbRegionByLine = 10;
    cptFrames = 0;
    nbImg = 0;
    starter = 0;
}

LearnWindowState::~LearnWindowState() {

}

void LearnWindowState::execute( WindowContext &context , Mat &cameraFeed ) {

    ofstream file("test.txt", ios::out | ios::app);

    if( !file ){
        cerr << "Impossible d'ouvrir le fichier !" << endl;
        exit(0);
    }

    skinMat = frames.getSkin( cameraFeed );
    fullHand = frames.getFullHand( skinMat );

    if(starter >= 50){
        if(cptFrames == 10){
            file  << frames.getFormatedSVM(fullHand,nbRegionByLine) << endl;
            cptFrames = 0;
            cout << nbImg++ << endl;
        }
        else cptFrames++;
    }
    else cout << " " << starter++ << endl;

    if( nbImg >= 110 )
        context.setState( new DefaultWindowState() );

    context.getWindow()->setMainMat( skinMat );
    context.getWindow()->setSecondaryMat( fullHand );
    context.getWindow()->setInfoLabel();
    context.getWindow()->show();

    waitKey(10);
}
