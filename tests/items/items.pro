
QT       += qml testlib
QT       -= gui

TARGET    = tst_itemstest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += tst_itemstest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
