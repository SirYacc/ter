#include "abstractwindow.h"

AbstractWindow::AbstractWindow(string model, QWidget *parent )
    : QWidget( parent ),
      model( model )
{
    _mainLabel = new QLabel();
    _secondaryLabel = new QLabel();

    int YcbCr[6];
    frames.getYCbCr(YcbCr);

    setMainLabel();
    setSecondaryLabel();

    QGridLayout *gLayout = new QGridLayout();
    QVBoxLayout *rightLayout = new QVBoxLayout();
    QGridLayout *leftLayout = new QGridLayout();
    QGridLayout *oLayout = new QGridLayout();
    QVBoxLayout *yLayout = new QVBoxLayout();
    QVBoxLayout *cbLayout = new QVBoxLayout();
    QVBoxLayout *crLayout = new QVBoxLayout();


    QGridLayout *sLayout = new QGridLayout();

    QString stlyeSheetBox = "QGroupBox{border: 1px solid gray; margin-top: 25px;}QGroupBox::title {subcontrol-origin: margin;subcontrol-position: top left;}";
    QGroupBox *yBox = new QGroupBox();
    yBox->setTitle("Y min/max");
    yBox->setStyleSheet(stlyeSheetBox);


    QGroupBox *cbBox = new QGroupBox();
    cbBox->setTitle("Cb min/max");
    cbBox->setStyleSheet( "QGroupBox{border: 1px solid gray;}");
    cbBox->setStyleSheet(stlyeSheetBox);

    QGroupBox *crBox = new QGroupBox();
    crBox->setTitle("Cr min/max");
    crBox->setStyleSheet( "QGroupBox{border: 1px solid gray;}");
    crBox->setStyleSheet(stlyeSheetBox);


    leftLayout->addWidget(_mainLabel,0,0,Qt::AlignTop);
    rightLayout->addWidget(_secondaryLabel);


    buttonRP = new QPushButton();
    buttonRP->setText("Run predict");
    buttonRP->setFixedWidth(300);
    buttonRP->connect(buttonRP, SIGNAL(released()), this, SLOT(setModeP()));

    buttonRL = new QPushButton();
    buttonRL->setText("Run learn");
    buttonRL->setFixedWidth(300);
    buttonRL->connect(buttonRL, SIGNAL(released()), this, SLOT(setModeL()));


    buttonC = new QPushButton();
    buttonC->setText("Run calibrage");
    buttonC->setFixedWidth(300);
    buttonC->connect(buttonC, SIGNAL(released()), this, SLOT(setModeC0()));


    buttonLand = new QPushButton();
    buttonLand->setText("Landing");
    buttonLand->setFixedWidth(300);
    buttonLand->connect(buttonLand, SIGNAL(released()), this, SLOT(setLanding()));

    buttonCam = new QPushButton();
    buttonCam->setText("Change camera feed");
    buttonCam->setFixedWidth(300);
    buttonCam->connect(buttonCam, SIGNAL(released()), this, SLOT(onChangeCameraFeedClicked()));

    rightLayout->addWidget(buttonRP);
    rightLayout->addWidget(buttonRL);
    rightLayout->addWidget(buttonC);
    rightLayout->addWidget(buttonLand);
    rightLayout->addWidget(buttonCam);


    yMinSlider = new QSlider(Qt::Horizontal);
    yMinSlider->setOrientation(Qt::Horizontal);
    yMinSlider->setFixedWidth(150);
    yMinSlider->setMaximum(255);
    yMinSlider->setMinimum(0);
    yMinSlider->setValue(YcbCr[0]);
    yMinSlider->connect(yMinSlider, SIGNAL(valueChanged(int)),
             this, SLOT(setYMin(int)));

    yMaxSlider = new QSlider(Qt::Horizontal);
    yMaxSlider->setOrientation(Qt::Horizontal);
    yMaxSlider->setFixedWidth(150);
    yMaxSlider->setMaximum(255);
    yMaxSlider->setMinimum(0);
    yMaxSlider->setValue(YcbCr[1]);
    yMaxSlider->connect(yMaxSlider, SIGNAL(valueChanged(int)),
             this, SLOT(setYMax(int)));

    yLayout->addWidget(yMinSlider);
    yLayout->addWidget(yMaxSlider);
    yBox->setLayout(yLayout);


    CrMinSlider = new QSlider(Qt::Horizontal);
    CrMinSlider->setOrientation(Qt::Horizontal);
    CrMinSlider->setFixedWidth(150);
    CrMinSlider->setMaximum(255);
    CrMinSlider->setMinimum(0);
    CrMinSlider->setValue(YcbCr[2]);
    CrMinSlider->connect(CrMinSlider, SIGNAL(valueChanged(int)),
             this, SLOT(setCrMin(int)));

    CrMaxSlider = new QSlider(Qt::Horizontal);
    CrMaxSlider->setOrientation(Qt::Horizontal);
    CrMaxSlider->setFixedWidth(150);
    CrMaxSlider->setMaximum(255);
    CrMaxSlider->setMinimum(0);
    CrMaxSlider->setValue(YcbCr[3]);
    CrMaxSlider->connect(CrMaxSlider, SIGNAL(valueChanged(int)),
             this, SLOT(setCrMax(int)));

    crLayout->addWidget(CrMinSlider);
    crLayout->addWidget(CrMaxSlider);
    crBox->setLayout(crLayout);


    CbMinSlider = new QSlider(Qt::Horizontal);
    CbMinSlider->setOrientation(Qt::Horizontal);
    CbMinSlider->setFixedWidth(150);
    CbMinSlider->setMaximum(255);
    CbMinSlider->setMinimum(0);
    CbMinSlider->setValue(YcbCr[4]);
    CbMinSlider->connect(CbMinSlider, SIGNAL(valueChanged(int)),
             this, SLOT(setCbMin(int)));

    CbMaxSlider = new QSlider(Qt::Horizontal);
    CbMaxSlider->setOrientation(Qt::Horizontal);
    CbMaxSlider->setFixedWidth(150);
    CbMaxSlider->setMaximum(255);
    CbMaxSlider->setMinimum(0);
    CbMaxSlider->setValue(YcbCr[5]);
    CbMaxSlider->connect(CbMaxSlider, SIGNAL(valueChanged(int)),
             this, SLOT(setCbMax(int)));

    cbLayout->addWidget(CbMinSlider);
    cbLayout->addWidget(CbMaxSlider);
    cbBox->setLayout(cbLayout);

    sLayout->addWidget(yBox,0,0);
    sLayout->addWidget(crBox,0,1);
    sLayout->addWidget(cbBox,0,2);

    QLabel *batterie = new QLabel("Batterie : 0%");

    oLayout->addWidget(batterie,0,0,Qt::AlignTop|Qt::AlignLeft);
    oLayout->addLayout(sLayout,0,1,Qt::AlignRight);
    sLayout->setMargin(25);
    leftLayout->addLayout(oLayout,1,0,Qt::AlignLeft);

    gLayout->addLayout(leftLayout,0,0,Qt::AlignTop);
    gLayout->addLayout(rightLayout,0,1,Qt::AlignTop|Qt::AlignLeft);

    setLayout(gLayout);
}

void AbstractWindow::setMainLabel()
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
    }
}

void AbstractWindow::setSecondaryLabel()
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
    }
}

void AbstractWindow::setMainMat(const Mat &newmat)
{
    _mainMat = newmat;
    setMainLabel();
}

void AbstractWindow::setSecondaryMat(const Mat &newmat)
{
    _secondaryMat = newmat;
    setSecondaryLabel();
}

void AbstractWindow::setModeP() {

    if( cameraFeed.dims == 0 )
        return;

    inFlightMode( true );
    context->setState( new PredictWindowState( model, frames ) );
}

void AbstractWindow::inFlightMode( bool mode ) {
    buttonRP->setDisabled( mode );
    buttonRL->setDisabled( mode );
    buttonC->setDisabled( mode );
    buttonCam->setDisabled( mode );
}

void AbstractWindow::setModeC0() {

    if( cameraFeed.dims == 0 )
        return;

    inCalibrateMode( true );

    buttonC->disconnect(SIGNAL(released()));
    buttonC->setText( "Capture" );
    buttonC->connect(buttonC, SIGNAL(released()), this, SLOT(setModeC1()));
    context->setState( new CalibrateWindowState0( cameraFeed ) );
}

void AbstractWindow::setModeC1() {

    if( cameraFeed.dims == 0 )
        return;

    inCalibrateMode( false );

    buttonC->disconnect(SIGNAL(released()));
    buttonC->setText( "Calibrate" );
    buttonC->connect(buttonC, SIGNAL(released()), this, SLOT(setModeC0()));
    context->setState( new CalibrateWindowState1( cameraFeed, frames ) );

    yMinSlider->setValue(frames.getYMin());
    yMaxSlider->setValue(frames.getYMax());

    CrMinSlider->setValue(frames.getCrMin());
    CrMaxSlider->setValue(frames.getCrMax());

    CbMinSlider->setValue(frames.getCbMin());
    CbMaxSlider->setValue(frames.getCbMax());
}

void AbstractWindow::inCalibrateMode( bool mode ) {
    buttonRP->setDisabled( mode );
    buttonRL->setDisabled( mode );
    buttonLand->setDisabled( mode );
    buttonCam->setDisabled( mode );
}

void AbstractWindow::setModeL() {

    if( cameraFeed.dims == 0 )
        return;

    context->setState( new LearnWindowState( "test.txt", frames ) );
}

void AbstractWindow::setLanding() {
    order = 1;
    inFlightMode( false );
    context->setState( new DefaultWindowState() );
}

void AbstractWindow::onChangeCameraFeedClicked(){
    ihm = false;
}
