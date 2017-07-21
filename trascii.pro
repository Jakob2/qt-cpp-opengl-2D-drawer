#-------------------------------------------------
#
# Project created by QtCreator 2017-07-17T09:42:53
#
#-------------------------------------------------

QT       += core gui opengl sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = trascii
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    grid.cpp \
    sign.cpp \
    menu.cpp \
    db.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    global.h \
    grid.h \
    sign.h \
    menu.h \
    db.h

FORMS    += mainwindow.ui

LIBS += -lglut -lGLU

QMAKE_CXXFLAGS += -std=c++11
