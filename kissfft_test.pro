#-------------------------------------------------
#
# Project created by QtCreator 2014-02-06T22:48:36
#
#-------------------------------------------------

QT  += core gui



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = kissfft_test
TEMPLATE = app



SOURCES += main.cpp\
        mainwindow.cpp \
       kiss_fft130/kiss_fft.c \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
       kiss_fft130/kiss_fft.h \
    kiss_fft130/kissfft.hh \
    qcustomplot.h

FORMS    += mainwindow.ui

