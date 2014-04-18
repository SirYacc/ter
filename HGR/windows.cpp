#include "windows.h"

using namespace std;
using namespace cv;

extern int order;
extern IplImage *imgFromKarmen;

Windows::Windows(int argc, char *argv[],HGRSVM svm, string file ,QWidget *parent): QWidget(parent)
{
    Q_UNUSED (parent)
    hgrsvm = svm;
    //  a = QApplication (argc, argv);
    mode = 0;
    model = file;

    square_len = 20;
    NSAMPLES = 6;


    _mainLabel = new QLabel();
    _secondaryLabel = new QLabel();

    setMainLabel();
    setSecondaryLabel();

    QGridLayout *gLayout = new QGridLayout;
    QVBoxLayout *bLayout = new QVBoxLayout;

    gLayout->addWidget(_mainLabel,0,0,Qt::AlignTop);
    bLayout->addWidget(_secondaryLabel);

    buttonRPC = new QPushButton();
    buttonRPC->setText("Run predict C");
    buttonRPC->setFixedWidth(300);
    buttonRPC->connect(buttonRPC, SIGNAL(released()), this, SLOT(setModePC()));


    buttonRPD = new QPushButton();
    buttonRPD->setText("Run predict D");
    buttonRPD->setFixedWidth(300);
    buttonRPD->connect(buttonRPD, SIGNAL(released()), this, SLOT(setModePD()));

    buttonRL = new QPushButton();
    buttonRL->setText("Run learn");
    buttonRL->setFixedWidth(300);
    buttonRL->connect(buttonRL, SIGNAL(released()), this, SLOT(setModeL()));


    buttonC = new QPushButton();
    buttonC->setText("Run calibrage");
    buttonC->setFixedWidth(300);
    buttonC->connect(buttonC, SIGNAL(released()), this, SLOT(setModeC()));


    buttonLand = new QPushButton();
    buttonLand->setText("Landing");
    buttonLand->setFixedWidth(300);
    buttonLand->connect(buttonLand, SIGNAL(released()), this, SLOT(setLanding()));

    bLayout->addWidget(buttonRPC);
    bLayout->addWidget(buttonRPD);
    bLayout->addWidget(buttonRL);
    bLayout->addWidget(buttonC);
    bLayout->addWidget(buttonLand);

    gLayout->addLayout(bLayout,0,1,Qt::AlignTop|Qt::AlignLeft);

    //addButton->connect(addButton,SIGNAL(released()),this,SLOT(addButtonSlot()));

    setLayout(gLayout);
    //runDefault();
    capture.open(0);
}

int Windows::runLearn(string filePath){
    ofstream file(filePath.c_str(), ios::out | ios::trunc);

    if(!file){
        cerr << "Impossible d'ouvrir le fichier !" << endl;
        exit(0);
    }

    Mat cameraFeed;
    Mat skinMat;
    Mat fullHand;

    int nbRegionByLine = 10;
    int cptFrames = 0;
    int nbImg = 0;
    int starter = 0;


    while(mode == 4){

        //store image to matrix
        capture.read(cameraFeed);

        skinMat= frames.getSkin(cameraFeed);

        // Creation des .txt
        //on prend une photo toute les 10 frames

        fullHand = frames.getFullHand(skinMat);

        setMainMat(skinMat);
        setSecondaryMat(fullHand);
        show();

        if(starter >= 100){
            if(cptFrames == 10){
                file  << frames.getFormatedSVM(fullHand,nbRegionByLine) << endl;
                cptFrames = 0;
                cout << nbImg++ << endl;
            }
            else cptFrames++;
        }
        else cout << " " <<starter ++;

        int c = waitKey(10);
        if( (char)c == 'c' || nbImg >= 300)
            break;
    }
    file.close();
    changeRunMode();
    return 0;
}


int Windows::runPredictD(){

    Mat karmenMat = Mat(imgFromKarmen);

    Mat skinMat;
    Mat fullHand;

    int nbRegionByLine = 10;
    string line;
    CvSVM cvSvm;
    cvSvm.load(model.c_str());

    int cptLoop = 0;
    while(karmenMat.dims == 0 && mode == 2){

        karmenMat = Mat(imgFromKarmen);
        if(cptLoop == 0){
            cout << " En attente du drone ..." << endl;
            cptLoop = 900000;
        }
        else cptLoop --;
        int c = waitKey(10);

    }

    while(mode == 2){

        karmenMat = Mat(imgFromKarmen);

        //store image to matrix
        // capture.read(cameraFeed);

        //show the current image
        //imshow("Original Image",cameraFeed);

        skinMat= frames.getSkin(karmenMat);
        fullHand = frames.getFullHand(skinMat);
        setMainMat(skinMat);
        setSecondaryMat(fullHand);
        show();

        line = frames.getFormatedSVM( fullHand, nbRegionByLine );

        // dataMat = svm.createPredictedData( line, nbRegionByLine );

        // cout << "Thumb  : " << cvSvm.predict( dataMat ) << endl;
        order = (int)hgrsvm.createPredictedData( line, nbRegionByLine );
        //cout << "Thumb  : " << order << endl;

        int c = waitKey(10);
        if( (char)c == 'c') {
            order = 1; // Land
            break;
        }
    }
    changeRunMode();
    return 0;
}


void Windows::runPredictC(){

    Mat cameraFeed;
    Mat skinMat;
    Mat fullHand ;
    int nbRegionByLine = 10;
    string line;
    CvSVM cvSvm;
    cvSvm.load(model.c_str());

    while(mode == 1){

        //store image to matrix
        capture.read(cameraFeed);

        //show the current image
        //imshow("Original Image",cameraFeed);

        skinMat= frames.getSkin(cameraFeed);
        fullHand = frames.getFullHand(skinMat);
        setMainMat(skinMat);
        setSecondaryMat(fullHand);

        line = frames.getFormatedSVM( fullHand, nbRegionByLine );

        order = (int)hgrsvm.createPredictedData( line, nbRegionByLine );
      //  cout << "Thumb  : " << order << endl;


        show();



        int c = waitKey(10);
        if( (char)c == 'c') {
            order = 1; // Land
            break;
        }
    }
    changeRunMode();
}




int Windows::getMedian(vector<int> val){

    int median;
    size_t size = val.size();

    sort(val.begin(), val.end());

    if (size  % 2 == 0)  {
        median = val[size / 2 - 1] ;
    } else{
        median = val[size / 2];
    }

    return median;
}

void Windows::getAvgColor( Mat m, My_ROI roi, int avg[3]) {

    (void)m;
    Mat r;
    vector<int>Y;
    vector<int>Cr;
    vector<int>Cb;

    roi.roi_ptr.copyTo(r);
    cvtColor( r, r, COLOR_BGR2YCrCb );

    for( int i = 2 ; i < r.rows-2 ; i++ ){
        for( int j = 2 ; j < r.cols-2 ; j++ ){
            Y.push_back(r.data[r.channels()*(r.cols*i + j) + 0]) ;
            Cr.push_back(r.data[r.channels()*(r.cols*i + j) + 1]) ;
            Cb.push_back(r.data[r.channels()*(r.cols*i + j) + 2]) ;
        }
    }

    avg[0] = getMedian(Y);
    avg[1] = getMedian(Cr);
    avg[2] = getMedian(Cb);


}


void Windows::minMaxValuesOfYCrCb( int min[3], int max[3] ) {

    for( int i = 0 ; i < NSAMPLES ; i++ ) {
        for( int j = 0 ; j < 3 ; j++ ) {
            if (avgColor[i][j] < min[j])
                min[j] = avgColor[i][j];
            if (avgColor[i][j] > max[j])
                max[j] = avgColor[i][j];
        }
    }
}

void Windows::calibrate() {
    Mat m;
    capture >> m;

    int min[3] = {255, 255, 255};
    int max[3] = {0, 0, 0};

    for( int j = 0 ; j < NSAMPLES ; j++ )
        getAvgColor( m, roi[j], avgColor[j]);

    minMaxValuesOfYCrCb( min, max );
    frames.setYCrCbMin( 0, min[1], min[2]-30 );
    frames.setYCrCbMax( 255, max[1]+60, max[2]+40 );
}

void Windows::runCalibrate(){

    Mat cameraFeed;
    Mat blackSq = Mat::zeros( Size(300,300), CV_8UC1 );


    capture.read(cameraFeed);

        roi.push_back( My_ROI(Point(cameraFeed.cols/4, cameraFeed.rows/2)      ,Point(cameraFeed.cols/4+square_len,cameraFeed.rows/2+square_len)     ,cameraFeed));
        roi.push_back( My_ROI(Point(cameraFeed.cols/3, cameraFeed.rows/1.5)    ,Point(cameraFeed.cols/3+square_len,cameraFeed.rows/1.5+square_len)   ,cameraFeed));
        roi.push_back( My_ROI(Point(cameraFeed.cols/2, cameraFeed.rows/2)      ,Point(cameraFeed.cols/2+square_len,cameraFeed.rows/2+square_len)     ,cameraFeed));
        roi.push_back( My_ROI(Point(cameraFeed.cols/2.5, cameraFeed.rows/2.5)  ,Point(cameraFeed.cols/2.5+square_len,cameraFeed.rows/2.5+square_len) ,cameraFeed));
        roi.push_back( My_ROI(Point(cameraFeed.cols/2, cameraFeed.rows/1.5)    ,Point(cameraFeed.cols/2+square_len,cameraFeed.rows/1.5+square_len)   ,cameraFeed));
        roi.push_back( My_ROI(Point(cameraFeed.cols/2.5, cameraFeed.rows/1.8)  ,Point(cameraFeed.cols/2.5+square_len,cameraFeed.rows/1.8+square_len) ,cameraFeed));


    while(mode == 3){

        //store image to matrix
        capture.read(cameraFeed);


        for( int j = 0 ; j < NSAMPLES ; j++ ){
            roi[j].draw_rectangle( cameraFeed );
        }
        setMainMat(cameraFeed);
        setSecondaryMat(blackSq);

        show();


        int c = waitKey(10);
        if( (char)c == 'c') {
            break;
        }
    }
    calibrate();
    changeRunMode();
}

void Windows::runDefault(){


    Mat cameraFeed;
    Mat blackSq = Mat::zeros( Size(300,300), CV_8UC1 );
    mode = 0;
    while(mode == 0){

        //store image to matrix
        capture.read(cameraFeed);
        setMainMat(cameraFeed);
        setSecondaryMat(blackSq);

        show();

        int c = waitKey(10);
        if( (char)c == 'c') {
            break;
        }
    }
    changeRunMode();
}

void Windows::setModePC(){
    this->mode = 1;
}

void Windows::setModePD(){
    this->mode = 2;
}

void Windows::setModeC(){
    this->mode = 3;
}

void Windows::setModeL(){
    this->mode = 4;
}

void Windows::setLanding(){
    order = 0;
    this->mode = 0;
}


void Windows::setMainMat(const Mat &newmat)
{
    _mainMat = newmat;
    setMainLabel();
}

void Windows::setSecondaryMat(const Mat &newmat)
{
    _secondaryMat = newmat;
    setSecondaryLabel();
}

void Windows::setMainLabel()
{

    if(_mainMat.cols*_mainMat.rows)
    {
        Mat rgb;
        QPixmap p;

        if(_mainMat.channels() == 3){
            cvtColor(_mainMat, rgb, CV_BGR2RGB);
            p.convertFromImage(QImage(rgb.data, rgb.cols, rgb.rows, QImage::Format_RGB888));
        }
        else if (_mainMat.channels() == 1){
            cvtColor(_mainMat, rgb, CV_GRAY2RGB);
            p.convertFromImage(QImage(rgb.data, rgb.cols, rgb.rows, QImage::Format_RGB888));
        }


        _mainLabel->setPixmap(p);
        //  resize(_mainMat.cols, _mainMat.rows);
    }
}

void Windows::setSecondaryLabel()
{

    if(_secondaryMat.cols*_secondaryMat.rows)
    {
        Mat rgb;
        QPixmap p;

        if(_secondaryMat.channels() == 3){
            cvtColor(_secondaryMat, rgb, CV_BGR2RGB);
            p.convertFromImage(QImage(rgb.data, rgb.cols, rgb.rows, QImage::Format_RGB888));
        }
        else if (_secondaryMat.channels() == 1){
            cvtColor(_secondaryMat, rgb, CV_GRAY2RGB);
            p.convertFromImage(QImage(rgb.data, rgb.cols, rgb.rows, QImage::Format_RGB888));
        }

        _secondaryLabel->setPixmap(p);
        // resize(_secondaryMat.cols, _secondaryMat.rows);
    }
}

void Windows::changeRunMode(){
    switch(mode){
    case 1 : runPredictC();
        break;
    case 2 : runPredictD();
        break;
    case 3 : runCalibrate();
        break;
    case 4 : runLearn("test.txt");
        break;
    default : runDefault();
        break;
    }
}

Windows::~Windows(){

}
