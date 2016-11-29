#-------------------------------------------------
#
# Project created by QtCreator 2016-11-21T14:38:51
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = evolution
TEMPLATE = app


SOURCES += main.cpp\
        evolution.cpp \
    fieldcell.cpp \
    lifecell.cpp

HEADERS  += evolution.h \
    fieldcell.h \
    lifecell.h \
    defines.h
