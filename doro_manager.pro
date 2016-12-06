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
    delegate.cpp \
    checkbox_model.cpp

HEADERS  += doro_manager.h \
    connection.h \
    delegate.h \
    checkbox_model.h

FORMS    += doro_manager.ui

RESOURCES += resources.qrc
