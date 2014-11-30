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
    newuserdialog.cpp \
    existinguserdialog.cpp \
    gamescreen.cpp \
    sun.cpp \
    gamehud.cpp \
    plant.cpp \
    peashooter.cpp \
    bullet.cpp \
    zombie.cpp \
    regularzombie.cpp \
    sunflower.cpp \
    walnut.cpp \
    cherrybomb.cpp \
    chomper.cpp \
    repeater.cpp \
    potatomine.cpp \
    coneheadzombie.cpp \
    newspaperzombie.cpp \
    bucketheadzombie.cpp \
    flagzombie.cpp

HEADERS  += mainwindow.h \
    newuserdialog.h \
    existinguserdialog.h \
    gamescreen.h \
    sun.h \
    gamehud.h \
    plant.h \
    peashooter.h \
    bullet.h \
    zombie.h \
    regularzombie.h \
    sunflower.h \
    walnut.h \
    cherrybomb.h \
    chomper.h \
    repeater.h \
    potatomine.h \
    coneheadzombie.h \
    newspaperzombie.h \
    bucketheadzombie.h \
    flagzombie.h

FORMS    += mainwindow.ui \
    newuserdialog.ui \
    existinguserdialog.ui

RESOURCES += \
    PvZ_assests.qrc
