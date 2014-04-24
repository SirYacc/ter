#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QPushButton>

#include "abstractwindow.h"
#include "webcamwindow.h"
#include "dronewindow.h"

class MyMainWindow : public QWidget
{
    Q_OBJECT
private:
    QStackedWidget *stackedWidget;

    QPushButton *droneButton;
    QPushButton *webcamButton;

    AbstractWindow *webcamWin;
    AbstractWindow *droneWin;

public:
    MyMainWindow( QStackedWidget *stackedWidget, QWidget *parent = 0 );

private slots:
    void setModeDrone();
    void setModeWebcam();
};

#endif // MAINWINDOW_H
