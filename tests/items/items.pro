
QT      += qml quick
QT      -= gui

TARGET   = tst_itemstest
CONFIG  += console qmltestcase
CONFIG  -= app_bundle

TEMPLATE = app

DESTDIR  = $$PWD/../../bin

SOURCES += tst_itemstest.cpp

OTHER_FILES += \
    cases/tst_GhostTree.qml \
    cases/tst_GhostNode.qml \
    cases/tst_Blackboard.qml \
    cases/tst_CompositeNode.qml \
    cases/tst_DecoratorNode.qml \
    cases/tst_LeafNode.qml \
    cases/tst_ActionNode.qml \
    cases/tst_SequenceNode.qml \
    cases/tst_SelectorNode.qml \
    cases/tst_ParallelNode.qml
