#-------------------------------------------------
#
# Project created by QtCreator 2017-05-06T14:34:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NonLinear
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sofunction.cpp \
    solvers/regulafalsi.cpp \
    solvers/common.cpp \
    backend.cpp \
    solvers/secant.cpp

HEADERS  += mainwindow.h \
    function.h \
    sofunction.h \
    solvers/regulafalsi.h \
    solvers/common.h \
    backend.h \
    solvers/secant.h

FORMS    += mainwindow.ui

LIBS += -ldl
