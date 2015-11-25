#-------------------------------------------------
#
# Project created by QtCreator 2015-11-16T14:47:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TARGET = AudioSignalSpectrum
TEMPLATE = app


SOURCES += main.cpp\
        audiosignalspectrumwindow.cpp \
    inputdatadialog.cpp

HEADERS  += audiosignalspectrumwindow.h \
    inputdatadialog.h

FORMS    += audiosignalspectrumwindow.ui \
    inputdatadialog.ui
