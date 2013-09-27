#-------------------------------------------------
#
# Project created by QtCreator 2013-09-21T17:12:17
#
#-------------------------------------------------

QT       += core gui network opengl widgets printsupport

TARGET = imu-viewer
TEMPLATE = app

LIBS += -lGL -lGLU -lglut

SOURCES += main.cpp\
        mainwindow.cpp \
    tcpclient.cpp \
    core.cpp \
    visualization.cpp \
    qcustomplot.cpp \
    dataplot.cpp

HEADERS  += mainwindow.h \
    tcpclient.h \
    core.h \
    visualization.h \
    qcustomplot.h \
    dataplot.h
