TEMPLATE = app

QT      += qml quick
CONFIG  -= app_bundle

SOURCES += main.cpp

DESTDIR  = $$PWD/../../bin

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = $$PWD/../../qml

# Default rules for deployment.
include(deployment.pri)
