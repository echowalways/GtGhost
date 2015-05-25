INCLUDEPATH += $$PWD

CONFIG  += unittest

HEADERS += \
    $$PWD/gtghostnamespace.h \
    $$PWD/gghostnode.h \
    $$PWD/gghostnode_p.h \
    $$PWD/gghosttree.h \
    $$PWD/gghosttree_p.h \
    $$PWD/gghostitem.h \
    $$PWD/gghostitem_p.h \
    $$PWD/gcompositeitem.h \
    $$PWD/gcompositeitem_p.h \
    $$PWD/glinearselectoritem.h \
    $$PWD/glinearselectoritem_p.h \
    $$PWD/glinearsequenceitem.h \
    $$PWD/glinearsequenceitem_p.h \
    $$PWD/gweightselectoritem.h \
    $$PWD/gweightselectoritem_p.h \
    $$PWD/gweightsequenceitem.h \
    $$PWD/gweightsequenceitem_p.h \
    $$PWD/grandomselectoritem.h \
    $$PWD/grandomselectoritem_p.h \
    $$PWD/grandomsequenceitem.h \
    $$PWD/grandomsequenceitem_p.h \
    $$PWD/gdecoratoritem.h \
    $$PWD/gdecoratoritem_p.h \
    $$PWD/ginverteritem.h \
    $$PWD/ginverteritem_p.h \
    $$PWD/grepeateritem.h \
    $$PWD/grepeateritem_p.h \
    $$PWD/galwaysfailureitem.h \
    $$PWD/galwaysfailureitem_p.h \
    $$PWD/galwayssuccessitem.h \
    $$PWD/galwayssuccessitem_p.h \
    $$PWD/grepeatuntilfailureitem.h \
    $$PWD/grepeatuntilfailureitem_p.h \
    $$PWD/grepeatuntilsuccessitem.h \
    $$PWD/grepeatuntilsuccessitem_p.h \
    $$PWD/gconditionitem.h \
    $$PWD/gconditionitem_p.h \
    $$PWD/gactionitem.h \
    $$PWD/gactionitem_p.h

SOURCES += \
    $$PWD/gghostnode.cpp \
    $$PWD/gghosttree.cpp \
    $$PWD/gghostitem.cpp \
    $$PWD/gcompositeitem.cpp \
    $$PWD/glinearselectoritem.cpp \
    $$PWD/glinearsequenceitem.cpp \
    $$PWD/gweightselectoritem.cpp \
    $$PWD/gweightsequenceitem.cpp \
    $$PWD/grandomselectoritem.cpp \
    $$PWD/grandomsequenceitem.cpp \
    $$PWD/gdecoratoritem.cpp \
    $$PWD/ginverteritem.cpp \
    $$PWD/grepeateritem.cpp \
    $$PWD/galwaysfailureitem.cpp \
    $$PWD/galwayssuccessitem.cpp \
    $$PWD/grepeatuntilfailureitem.cpp \
    $$PWD/grepeatuntilsuccessitem.cpp \
    $$PWD/gconditionitem.cpp \
    $$PWD/gactionitem.cpp

unittest {
QT      += testlib

DEFINES += GT_GHOST_UNITTEST

HEADERS += \
    $$PWD/gghostunittest.h \
    $$PWD/gghostunittest_p.h

SOURCES +=  \
    $$PWD/gghostunittest.cpp
}
