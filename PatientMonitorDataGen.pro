#-------------------------------------------------
#
# Project created by QtCreator 2016-08-31T09:01:49
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PatientMonitorDataGen
TEMPLATE = app


SOURCES += main.cpp \
           PatientMonitorDataGen.cpp \
		   myserver.cpp \
           mainwindow.cpp

HEADERS  += mainwindow.h PatientMonitorDataGen.h myserver.h

FORMS    += mainwindow.ui
