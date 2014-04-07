TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/local/include/opencv
LIBS += `pkg-config --libs opencv`

SOURCES += main.cpp \
    windows.cpp \
    hgrsvm.cpp \
    frames.cpp

HEADERS += \
    windows.h \
    hgrsvm.h \
    frames.h

