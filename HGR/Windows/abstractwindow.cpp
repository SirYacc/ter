#include "abstractwindow.h"

AbstractWindow::AbstractWindow(string model, QWidget *parent )
    : QWidget( parent ),
      model( model )
{
    _mainLabel = new QLabel();
    _secondaryLabel = new QLabel();

    setMainLabel();
    setSecondaryLabel();

    QGridLayout *gLayout = new QGridLayout;
    QVBoxLayout *bLayout = new QVBoxLayout;

    gLayout->addWidget(_mainLabel,0,0,Qt::AlignTop);
    bLayout->addWidget(_secondaryLabel);

    buttonRP = new QPushButton();
    buttonRP->setText("Run predict");
    buttonRP->setFixedWidth(300);
    buttonRP->connect(buttonRP, SIGNAL(released()), this, SLOT(setModeP()));

    buttonRL = new QPushButton();
    buttonRL->setText("Run learn");
    buttonRL->setFixedWidth(300);
    buttonRL->connect(buttonRL, SIGNAL(released()), this, SLOT(setModeL()));

    buttonC = new QPushButton();
    buttonC->setText("Calibrate");
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

    bLayout->addWidget(buttonRP);
    bLayout->addWidget(buttonRL);
    bLayout->addWidget(buttonC);
    bLayout->addWidget(buttonLand);
    bLayout->addWidget(buttonCam);

    gLayout->addLayout(bLayout,0,1,Qt::AlignTop|Qt::AlignLeft);

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
    order = 0;
    inFlightMode( false );
    context->setState( new DefaultWindowState() );
}

void AbstractWindow::onChangeCameraFeedClicked() {
    ihm = false;
}
