#-------------------------------------------------
#
# Project created by QtCreator 2016-11-12T19:35:40
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SCFqt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    datalistini.cpp

HEADERS  += mainwindow.h \
    datalistini.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

