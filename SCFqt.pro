#-------------------------------------------------
#
# Project created by QtCreator 2016-11-12T19:35:40
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SCFqt
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
        mainwindow.cpp \
        datalistini.cpp \
    dbwizard.cpp \
    config.cpp \
    listino.cpp

HEADERS  += mainwindow.h \
            datalistini.h \
    dbwizard.h \
    config.h \
    connection.h \
    listino.h

FORMS    += mainwindow.ui

DISTFILES += \
    .gitignore \
    LICENSE \
    README.md \
    SCFqt.desktop \
    doc/L001-1r16-listino-021.pdf \
    metel/ARNLSP.txt \
    metel/BTILSP.TXT \
    metel/SNR0613.txt

DEFINES += APP_NAME=\\\"SCFqt\\\"
VERSION = 0.0.2
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

RESOURCES += \
    resources.qrc
