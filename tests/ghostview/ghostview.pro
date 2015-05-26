TEMPLATE = app

QT      += qml quick

SOURCES += main.cpp

DESTDIR  = $$PWD/../../bin

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = $$PWD/../../qml

# Default rules for deployment.
include(deployment.pri)
