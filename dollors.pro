#-------------------------------------------------
#
# Project created by QtCreator 2022-02-19T12:32:40
#
#-------------------------------------------------

QT       += core gui
QT       += sql widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dollors
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    tableWindow.cpp

HEADERS  += mainwindow.h \
    tableWindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    taiji.qrc

RC_FILE=taiji.rc
