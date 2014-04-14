TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

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
               ../ARDroneLib/                       \
               ../ARDroneLib/Soft/Lib/              \
               ../ARDroneLib/Soft/Lib/ardrone_tool/ \
               ../ARDroneLib/Soft/Common/           \
               ../ARDroneLib/VP_SDK/                \
               ../ARDroneLib/VP_SDK/VP_Os/linux/    \
               ../ARDroneLib/FFMPEG/Includes/



QMAKE_CXXFLAGS += \
            -pthread    \
            -D_REENTRANT\
            -D__LINUX__ \
            -std=c++0x


LIBS += `pkg-config --libs opencv gtk+-2.0 glib-2.0` \
        -lpc_ardrone                        \
        -lrt                                \
        -pthread

SOURCES += main.cpp                 \
    windows.cpp                     \
    hgrsvm.cpp                      \
    frames.cpp                      \
    ../Drone/ardrone_testing_tool.c \
    ../Drone/Video/pre_stage.c      \
    ../Drone/Video/post_stage.c     \
    ../Drone/Video/display_stage.c

HEADERS += \
    windows.h                       \
    hgrsvm.h                        \
    frames.h                        \
    ../Drone/ardrone_testing_tool.h \
    ../Drone/Video/pre_stage.h      \
    ../Drone/Video/post_stage.h     \
    ../Drone/Video/display_stage.h


unix:!macx: LIBS += -L$$PWD/../ARDroneLib/Soft/Build/targets_versions/ardrone_lib/ -lpc_ardrone

INCLUDEPATH += $$PWD/../ARDroneLib/Soft/Build/targets_versions/ardrone_lib
DEPENDPATH += $$PWD/../ARDroneLib/Soft/Build/targets_versions/ardrone_lib

unix:!macx: PRE_TARGETDEPS += $$PWD/../ARDroneLib/Soft/Build/targets_versions/ardrone_lib/libpc_ardrone.a

unix:!macx: LIBS += -L$$PWD/../ARDroneLib/Soft/Build/targets_versions/sdk/ -lsdk

INCLUDEPATH += $$PWD/../ARDroneLib/Soft/Build/targets_versions/sdk
DEPENDPATH += $$PWD/../ARDroneLib/Soft/Build/targets_versions/sdk

unix:!macx: PRE_TARGETDEPS += $$PWD/../ARDroneLib/Soft/Build/targets_versions/sdk/libsdk.a

unix:!macx: LIBS += -L$$PWD/../ARDroneLib/Soft/Build/targets_versions/vlib/ -lvlib

INCLUDEPATH += $$PWD/../ARDroneLib/Soft/Build/targets_versions/vlib
DEPENDPATH += $$PWD/../ARDroneLib/Soft/Build/targets_versions/vlib

unix:!macx: PRE_TARGETDEPS += $$PWD/../ARDroneLib/Soft/Build/targets_versions/vlib/libvlib.a

unix:!macx: LIBS += -L$$PWD/../ARDroneLib/Soft/Build/targets_versions/ffmpeg_static/ -lavcodec

INCLUDEPATH += $$PWD/../ARDroneLib/Soft/Build/targets_versions/ffmpeg_static
DEPENDPATH += $$PWD/../ARDroneLib/Soft/Build/targets_versions/ffmpeg_static

unix:!macx: PRE_TARGETDEPS += $$PWD/../ARDroneLib/Soft/Build/targets_versions/ffmpeg_static/libavcodec.a

unix:!macx: LIBS += -L$$PWD/../ARDroneLib/Soft/Build/targets_versions/ffmpeg_static/ -lavdevice

INCLUDEPATH += $$PWD/../ARDroneLib/Soft/Build/targets_versions/ffmpeg_static
DEPENDPATH += $$PWD/../ARDroneLib/Soft/Build/targets_versions/ffmpeg_static

unix:!macx: PRE_TARGETDEPS += $$PWD/../ARDroneLib/Soft/Build/targets_versions/ffmpeg_static/libavdevice.a

unix:!macx: LIBS += -L$$PWD/../ARDroneLib/Soft/Build/targets_versions/ffmpeg_static/ -lavfilter

INCLUDEPATH += $$PWD/../ARDroneLib/Soft/Build/targets_versions/ffmpeg_static
DEPENDPATH += $$PWD/../ARDroneLib/Soft/Build/targets_versions/ffmpeg_static

unix:!macx: PRE_TARGETDEPS += $$PWD/../ARDroneLib/Soft/Build/targets_versions/ffmpeg_static/libavfilter.a

unix:!macx: LIBS += -L$$PWD/../ARDroneLib/Soft/Build/targets_versions/ffmpeg_static/ -lavformat

INCLUDEPATH += $$PWD/../ARDroneLib/Soft/Build/targets_versions/ffmpeg_static
DEPENDPATH += $$PWD/../ARDroneLib/Soft/Build/targets_versions/ffmpeg_static

unix:!macx: PRE_TARGETDEPS += $$PWD/../ARDroneLib/Soft/Build/targets_versions/ffmpeg_static/libavformat.a

unix:!macx: LIBS += -L$$PWD/../ARDroneLib/Soft/Build/targets_versions/ffmpeg_static/ -lavutil

INCLUDEPATH += $$PWD/../ARDroneLib/Soft/Build/targets_versions/ffmpeg_static
DEPENDPATH += $$PWD/../ARDroneLib/Soft/Build/targets_versions/ffmpeg_static

unix:!macx: PRE_TARGETDEPS += $$PWD/../ARDroneLib/Soft/Build/targets_versions/ffmpeg_static/libavutil.a

unix:!macx: LIBS += -L$$PWD/../ARDroneLib/Soft/Build/targets_versions/ffmpeg_static/ -lswscale

INCLUDEPATH += $$PWD/../ARDroneLib/Soft/Build/targets_versions/ffmpeg_static
DEPENDPATH += $$PWD/../ARDroneLib/Soft/Build/targets_versions/ffmpeg_static

unix:!macx: PRE_TARGETDEPS += $$PWD/../ARDroneLib/Soft/Build/targets_versions/ffmpeg_static/libswscale.a
