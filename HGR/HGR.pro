QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = HGR
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

DEFINES += FFMPEG_SUPPORT

INCLUDEPATH += /usr/local/include/opencv            \
               /usr/include/gtk-2.0                 \
               /usr/lib/gtk-2.0/include             \
               /usr/include/atk-1.0                 \
               /usr/include/cairo                   \
               /usr/include/pango-1.0               \
               /usr/include/gio-unix-2.0/           \
               /usr/include/glib-2.0                \
               /usr/lib/glib-2.0/include            \
               /usr/include/pixman-1                \
               /usr/include/freetype2               \
               /usr/include/directfb                \
               /usr/include/libpng12                \
               /usr/lib/x86_64-linux-gnu/gtk-2.0/include \
               /usr/include/gdk-pixbuf-2.0 \
               /usr/lib/x86_64-linux-gnu/glib-2.0/include \

QMAKE_CXXFLAGS += \
            -pthread    \
            -D_REENTRANT\
            -D__LINUX__ \
            -std=c++0x \
            -D__STDC_CONSTANT_MACROS


LIBS += `pkg-config --libs opencv gtk+-2.0 glib-2.0` \
                -lm                     \
                -lpthread               \
                -lavutil                \
                -lavformat              \
                -lavcodec               \
                -lswscale               \
                -lopencv_core           \
                -lopencv_imgproc        \
                -lopencv_highgui

SOURCES += main.cpp                 \
    hgrsvm.cpp                      \
    frames.cpp                      \
    cvdrone/src/ardrone/ardrone.cpp                 \
    cvdrone/src/ardrone/command.cpp                 \
    cvdrone/src/ardrone/config.cpp                 \
    cvdrone/src/ardrone/navdata.cpp                 \
    cvdrone/src/ardrone/tcp.cpp                 \
    cvdrone/src/ardrone/udp.cpp                 \
    cvdrone/src/ardrone/version.cpp                 \
    cvdrone/src/ardrone/video.cpp                 \
    my_roi.cpp \
    windowcontext.cpp \
    WindowStates/defaultwindowstate.cpp \
    WindowStates/calibratewindowstate1.cpp \
    WindowStates/calibratewindowstate0.cpp \
    WindowStates/binarywindowstate.cpp \
    WindowStates/abstractwindowstate.cpp \
    WindowStates/learnwindowstate.cpp \
    Windows/mymainwindow.cpp \
    WindowStates/predictwindowstate.cpp \
    cvdrone/src/ardrone/mainArdrone.cpp \
    Strategy/dronestrategy.cpp \
    Strategy/webcamstrategy.cpp \
    Strategy/videostreamstrategy.cpp \
    Windows/mywindow.cpp

HEADERS += \
    hgrsvm.h                        \
    frames.h                        \
     cvdrone/src/ardrone/ardrone.h \
     cvdrone/src/ardrone/uvlc.h\
    my_roi.h \
    windowcontext.h \
    WindowStates/defaultwindowstate.h \
    WindowStates/calibratewindowstate1.h \
    WindowStates/calibratewindowstate0.h \
    WindowStates/binarywindowstate.h \
    WindowStates/abstractwindowstate.h \
    WindowStates/learnwindowstate.h \
    Windows/mymainwindow.h \
    WindowStates/predictwindowstate.h \
    Strategy/dronestrategy.h \
    Strategy/webcamstrategy.h \
    Strategy/videostreamstrategy.h \
    Windows/mywindow.h
