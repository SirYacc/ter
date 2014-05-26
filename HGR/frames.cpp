#include "frames.h"

using namespace std;
using namespace cv;

Frames::Frames(void)
{
    Y_MIN  = 0;
    Y_MAX  = 255;
    Cr_MIN = 133;
    Cr_MAX = 183;
    Cb_MIN = 77;
    Cb_MAX = 147;

//    Y_MIN  = 0;
//    Y_MAX  = 255;
//    Cr_MIN = 135;
//    Cr_MAX = 180;
//    Cb_MIN = 85;
//    Cb_MAX = 135;

//    Y_MIN  = 0;
//    Y_MAX  = 255;
//    Cr_MIN = 133;
//    Cr_MAX = 173;
//    Cb_MIN = 77;
//    Cb_MAX = 127;

}

Mat Frames::getSkin( Mat input ) {

    Mat skin;

    cvtColor( input, skin, COLOR_BGR2YCrCb );

    inRange( skin, Scalar( Y_MIN, Cr_MIN, Cb_MIN ), Scalar( Y_MAX, Cr_MAX, Cb_MAX ), skin );

    Mat Kernel( Size(2, 2), CV_8UC1 );
    Kernel.setTo( Scalar(3) );

    erode( skin, skin, Kernel );

    Kernel.setTo( Scalar(1) );
    dilate( skin, skin, Kernel );

    blur( skin, skin, Size(10,10) );

    threshold( skin, skin, 200, 255, THRESH_BINARY );

    return skin;
}


Rect Frames::getBoundingRectOfBiggestContour( Mat input ) {

    int largest_area=0;
    int largest_contour_index=0;
    Rect bounding_rect;
    vector<vector<Point> > contours; // Vector for storing contour
    vector<Vec4i> hierarchy;

    findContours( input, contours, hierarchy,CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
    //~ // iterate through each contour.
    for( unsigned int i = 0; i< contours.size(); i++ )
    {
        //  Find the area of contour
        double a=contourArea( contours[i],false);

        if(a>largest_area){
            largest_area=a;
            // Store the index of largest contour
            largest_contour_index=i;
            // Find the bounding rectangle for biggest contour
            bounding_rect=boundingRect(contours[i]);
        }
    }

    Scalar color( 255,255,255);  // color of the contour in the
    //Draw the contour and rectangle
    drawContours( input, contours,largest_contour_index, color, CV_FILLED,8,hierarchy);

    return bounding_rect;


}

void Frames::resizeRect( Rect *rect ){

    if(rect->width < rect->height){
        rect->x -= (rect->height - rect->width)/2;
        rect->width = rect->height;
    }
    else if(rect->height < rect->width){
        rect->y -= (rect->width - rect->height)/2;
        rect->height = rect->width;
    }

    rect->x -= 10;
    rect->width += 20;

    rect->y -= 10;
    rect->height += 20;
}

Mat Frames::getFullHand( Mat input ) {

    Mat hand = Mat::zeros( Size(300,300), CV_8UC1 );
    Rect bounding_rect;

    bounding_rect = getBoundingRectOfBiggestContour( input );

    resizeRect( &bounding_rect );

    if(!(bounding_rect.x + bounding_rect.width > input.cols) &&
            !(bounding_rect.y + bounding_rect.height > input.rows) &&
            bounding_rect.x > 0 && bounding_rect.y > 0)
        hand = input( bounding_rect );

    resize( hand, hand, Size(300,300), 0, 0, INTER_LANCZOS4 );

    rectangle(input,bounding_rect,Scalar(255,255,255));
    return hand;
}

//Point( y, x )
Mat Frames::divideFrameIntoSquares( Mat frame, int gridWidthInPixel ) {

    int width = frame.cols;
    int height = frame.rows;

    for (int i = gridWidthInPixel ; i < width ; i += gridWidthInPixel) {
        line( frame, Point( i, 0 ), Point( i, height ), Scalar( 255, 0, 0 ) );
        line( frame, Point( 0, i ), Point( width, i ) , Scalar( 255, 0, 0 ) );
    }

    return frame;
}

String Frames::convertToString( bool *tab, int size ) {

    ostringstream oss;

    for (int k = 0 ; k < size ; k++)
        oss << tab[k];

    return oss.str();
}

String Frames::getFormatedSVM( Mat frame, int nbRegionByLine ) {

    int nbRegions = nbRegionByLine*nbRegionByLine;
    int nbPixels = frame.cols / nbRegionByLine;

    bool reg[nbRegions];
    bool white = false;
    int r, k, j;

    for (r = 0 ; r <= nbRegions ; r++) {
        white = false;
        for (k = (r%nbRegionByLine)*nbPixels ; k < (r%nbRegionByLine)*nbPixels + nbPixels ; k++) {
            for (j = (r/nbRegionByLine)*nbPixels ; j < (r/nbRegionByLine)*nbPixels + nbPixels ; j++){
                if(frame.at<uchar>(j,k) == 255){
                    white = true;
                    break;
                }
            }
            if (white)
                break;
        }
        reg[r] = white;
    }

    return convertToString( reg, nbRegions );
}

void Frames::printTabOfRegion( bool *tab, int size, int nbCellByLine ) {

    cout << tab[0];
    for(int k = 1; k < size; k++) {
        if (k % nbCellByLine == 0)
            cout << "" << endl << tab[k];
        else
            cout << " - " << tab[k];
    }
    cout << "" << endl << "fin" << endl;
}

 Frames::~Frames(){

}
