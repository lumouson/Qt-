#-------------------------------------------------
#
# Project created by QtCreator 2022-09-08T11:30:01
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = design
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
INCLUDEPATH += D:/opencv/opencv3.4-qt-intall/install/include
INCLUDEPATH += D:/opencv/opencv3.4-qt-intall/install/include/opencv
INCLUDEPATH += D:/opencv/opencv3.4-qt-intall/install/include/opencv2
LIBS += D:/opencv/opencv3.4-qt-intall/install/x86/mingw/lib/libopencv_*.a
