#ifndef GREPEATERITEM_P_H
#define GREPEATERITEM_P_H

#include "gdecoratoritem_p.h"
#include "grepeateritem.h"

class GRepeaterItemPrivate : public GDecoratorItemPrivate
{
    Q_DECLARE_PUBLIC(GRepeaterItem)

public:
    GRepeaterItemPrivate();
    virtual ~GRepeaterItemPrivate();

public:
    virtual void onChildStatusChanged(GGhostItem *child) Q_DECL_FINAL;

public:
    virtual void executeChildItem() Q_DECL_FINAL;

public:
    int loopCount;
    int loopCounter;
};

#endif // GREPEATERITEM_P_H
