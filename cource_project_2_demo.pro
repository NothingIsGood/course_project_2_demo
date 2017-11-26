#-------------------------------------------------
#
# Project created by QtCreator 2017-11-12T16:10:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cource_project_2_demo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    task1lcs.cpp \
    task1view.cpp \
    task2matrix.cpp \
    task2view.cpp \
    abstractview.cpp

HEADERS  += mainwindow.h \
    abstracttask.h \
    task1lcs.h \
    exceptions.h \
    task1view.h \
    task2matrix.h \
    task2view.h \
    abstractview.h
