
TEMPLATE = lib
TARGET   = gtghostplugin
QT      += core-private qml qml-private
CONFIG  += qt plugin c++11 no_private_qt_headers_warning
DESTDIR  = $$clean_path($$PWD/../../qml/GtGhost)

HEADERS += $$PWD/gtghostplugin.h
SOURCES += $$PWD/gtghostplugin.cpp

include(kernel/kernel.pri)

!win {
    QMAKE_POST_LINK += $$PWD/scripts/make_other_files.sh
}
