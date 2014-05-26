#include "mymainwindow.h"

MyMainWindow::MyMainWindow(QStackedWidget *stackedWidget, QWidget *parent)
    : QWidget( parent ),
      stackedWidget( stackedWidget )
{
    QGridLayout *gLayout = new QGridLayout();

    droneButton = new QPushButton();
    droneButton->setText( "Drone" );
    droneButton->setFixedWidth( 250 );
    droneButton->setFixedHeight( 50 );
    droneButton->connect( droneButton, SIGNAL( released() ), this, SLOT( setModeDrone() ));

    webcamButton = new QPushButton();
    webcamButton->setText( "Webcam" );
    webcamButton->setFixedWidth( 250 );
    webcamButton->setFixedHeight( 50 );
    webcamButton->connect( webcamButton, SIGNAL( released() ), this, SLOT( setModeWebcam() ));

    gLayout->addWidget( droneButton, 2, 1, 2, 1 );
    gLayout->addWidget( webcamButton, 3, 1, 2, 1 );

    setLayout( gLayout );

    window = new MyWindow( "model.txt" );
    stackedWidget->addWidget( window );

    webcamStrategy = new WebcamStrategy();
    droneStrategy = new DroneStrategy();
}

void MyMainWindow::setModeDrone() {
    stackedWidget->setCurrentWidget( window );
    window->run( droneStrategy );
    stackedWidget->setCurrentWidget( this );
}

void MyMainWindow::setModeWebcam() {
    stackedWidget->setCurrentWidget( window );
    window->run( webcamStrategy );
    stackedWidget->setCurrentWidget( this );
}
