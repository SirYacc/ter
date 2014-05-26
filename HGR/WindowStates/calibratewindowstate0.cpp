#include "calibratewindowstate0.h"
#include "windowcontext.h"
#include "Windows/mywindow.h"

CalibrateWindowState0::CalibrateWindowState0( Mat cameraFeed )
    : blackSq( Mat::zeros( Size( 300, 300 ), CV_8UC1 ))
{
    square_len = 20;
    NSAMPLES = 6;
    setROI( cameraFeed );
}

void CalibrateWindowState0::setROI( Mat cameraFeed ) {

    roi.push_back( My_ROI( Point( cameraFeed.cols/4, cameraFeed.rows/2 ),
                           Point( cameraFeed.cols/4 + square_len, cameraFeed.rows/2 + square_len ),
                           cameraFeed) );
    roi.push_back( My_ROI( Point( cameraFeed.cols/3, cameraFeed.rows/1.5 ),
                           Point( cameraFeed.cols/3 + square_len, cameraFeed.rows/1.5 + square_len ),
                           cameraFeed) );
    roi.push_back( My_ROI( Point( cameraFeed.cols/2, cameraFeed.rows/2 ),
                           Point( cameraFeed.cols/2 + square_len, cameraFeed.rows/2 + square_len ),
                           cameraFeed) );
    roi.push_back( My_ROI( Point( cameraFeed.cols/2.5, cameraFeed.rows/2.5 ),
                           Point( cameraFeed.cols/2.5 + square_len, cameraFeed.rows/2.5 + square_len ),
                           cameraFeed) );
    roi.push_back( My_ROI( Point( cameraFeed.cols/2, cameraFeed.rows/1.5 ),
                           Point( cameraFeed.cols/2 + square_len, cameraFeed.rows/1.5 + square_len ),
                           cameraFeed) );
    roi.push_back( My_ROI( Point( cameraFeed.cols/2.5, cameraFeed.rows/1.8 ),
                           Point( cameraFeed.cols/2.5 + square_len, cameraFeed.rows/1.8 + square_len ),
                           cameraFeed) );
}

void CalibrateWindowState0::execute(WindowContext &context , Mat &cameraFeed) {

    for( int j = 0 ; j < NSAMPLES ; j++ )
        roi[j].draw_rectangle( cameraFeed );

    context.getWindow()->setMainMat( cameraFeed );
    context.getWindow()->setSecondaryMat( blackSq );
    context.getWindow()->setInfoLabel();
    context.getWindow()->show();

    waitKey( 0 );
}
