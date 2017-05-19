#-------------------------------------------------
#
# Project created by QtCreator 2013-09-25T09:11:42
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyOpenGL
TEMPLATE = app


SOURCES += main.cpp\
        window.cpp \
    myglwidget.cpp \
    webcam.cpp \
    textures.cpp \
    grid.cpp

HEADERS  += window.h \
    myglwidget.h \
    webcam.h \
    textures.h \
    grid.h

FORMS    += window.ui
INCLUDEPATH +=$$(OPENCV_DIR)\..\..\include
LIBS += -lOpengl32 \
     -lglu32 \
     -lglut \
    -L$$(OPENCV_DIR)\lib \
    -lopencv_core2413 \
    -lopencv_highgui2413 \
    -lopencv_imgproc2413 \
    #-lopencv_videoio2413 \
    -lopencv_features2d2413 \
    -lopencv_calib3d2413

RESOURCES += \
    ressources.qrc
