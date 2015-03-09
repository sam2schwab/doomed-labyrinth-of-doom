#-------------------------------------------------
#
# Project created by QtCreator 2015-03-09T11:29:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = doomed-labyrinth-of-doom
TEMPLATE = app

LIBS += -L./SFML/lib

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    main.h

FORMS    += mainwindow.ui

INCLUDEPATH += ./SFML/include
DEPENDPATH += ./SFML/include
