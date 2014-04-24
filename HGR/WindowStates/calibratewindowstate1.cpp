#include "calibratewindowstate1.h"
#include "windowcontext.h"

CalibrateWindowState1::CalibrateWindowState1( Mat cameraFeed, Frames & frames )
    : frames( frames ),
      blackSq( Mat::zeros( Size( 300, 300 ), CV_8UC1 ))
{
    square_len = 20;
    NSAMPLES = 6;
    setROI( cameraFeed );
}

void CalibrateWindowState1::setROI( Mat cameraFeed ) {

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

int CalibrateWindowState1::getMedian( vector< int > val ){

    int median;
    size_t size = val.size();

    sort( val.begin(), val.end() );

    if (size  % 2 == 0)  {
        median = val[size / 2 - 1] ;
    } else{
        median = val[size / 2];
    }

    return median;
}

void CalibrateWindowState1::getAvgColor( Mat m, My_ROI roi, int avg[3]) {

    (void)m;
    Mat r;
    vector< int > Y;
    vector< int > Cr;
    vector< int > Cb;

    roi.roi_ptr.copyTo( r );
    cvtColor( r, r, COLOR_BGR2YCrCb );

    for( int i = 2 ; i < r.rows-2 ; i++ ){
        for( int j = 2 ; j < r.cols-2 ; j++ ){
            Y.push_back( r.data[r.channels()*(r.cols*i + j) + 0] );
            Cr.push_back( r.data[r.channels()*(r.cols*i + j) + 1] );
            Cb.push_back( r.data[r.channels()*(r.cols*i + j) + 2] );
        }
    }

    avg[0] = getMedian(Y);
    avg[1] = getMedian(Cr);
    avg[2] = getMedian(Cb);
}

void CalibrateWindowState1::minMaxValuesOfYCrCb( int min[3], int max[3] ) {

    for( int i = 0 ; i < NSAMPLES ; i++ ) {
        for( int j = 0 ; j < 3 ; j++ ) {
            if (avgColor[i][j] < min[j])
                min[j] = avgColor[i][j];
            if (avgColor[i][j] > max[j])
                max[j] = avgColor[i][j];
        }
    }
}

void CalibrateWindowState1::calibrate( Mat cameraFeed ) {

    int min[3] = {255, 255, 255};
    int max[3] = {0, 0, 0};

    for( int j = 0 ; j < NSAMPLES ; j++ )
        getAvgColor( cameraFeed, roi[j], avgColor[j] );

    minMaxValuesOfYCrCb( min, max );
    frames.setYCrCbMin( 0, min[1], min[2]-30 );
    frames.setYCrCbMax( 255, max[1]+60, max[2]+40 );
}

void CalibrateWindowState1::execute(WindowContext &context , Mat &cameraFeed) {

    calibrate( cameraFeed );

    context.setState( new BinaryWindowState( frames ) );
}
