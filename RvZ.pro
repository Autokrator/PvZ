#-------------------------------------------------
#
# Project created by QtCreator 2014-11-08T13:15:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RvZ
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gamewindow.cpp \
    newuserdialog.cpp \
    existinguserdialog.cpp

HEADERS  += mainwindow.h \
    gamewindow.h \
    newuserdialog.h \
    existinguserdialog.h

FORMS    += mainwindow.ui \
    gamewindow.ui \
    newuserdialog.ui \
    existinguserdialog.ui
