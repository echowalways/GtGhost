
QT      += qml quick
QT      -= gui

TARGET   = tst_itemstest
CONFIG  += console qmltestcase
CONFIG  -= app_bundle

TEMPLATE = app

DESTDIR  = $$PWD/../../bin

SOURCES += tst_itemstest.cpp

DISTFILES += \
    cases/tst_ActionNode.qml
