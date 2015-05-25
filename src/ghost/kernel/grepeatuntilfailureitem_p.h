#ifndef GREPEATUNTILFAILUREITEM_P_H
#define GREPEATUNTILFAILUREITEM_P_H

#include "gdecoratoritem_p.h"
#include "grepeatuntilfailureitem.h"

class GRepeatUntilFailureItemPrivate : public GDecoratorItemPrivate
{
    Q_DECLARE_PUBLIC(GRepeatUntilFailureItem)

public:
    GRepeatUntilFailureItemPrivate();
    virtual ~GRepeatUntilFailureItemPrivate();

public:
    virtual void onChildStatusChanged(GGhostItem *child) Q_DECL_FINAL;

public:
    virtual void executeChildItem() Q_DECL_FINAL;

public:
    int loopCount;
    int loopCounter;
};

#endif // GREPEATUNTILFAILUREITEM_P_H
