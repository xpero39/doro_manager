#-------------------------------------------------
#
# Project created by QtCreator 2016-07-31T08:25:38
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

INCLUDEPATH += $$PWD

TARGET = doro_manager
TEMPLATE = app


SOURCES += main.cpp\
        doro_manager.cpp \
    delegate.cpp

HEADERS  += doro_manager.h \
    connection.h \
    delegate.h

FORMS    += doro_manager.ui

RESOURCES += resources.qrc

RC_ICONS = doro.ico
