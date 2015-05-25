#ifndef GINVERTERITEM_P_H
#define GINVERTERITEM_P_H

#include "gdecoratoritem_p.h"
#include "ginverteritem.h"

class GInverterItemPrivate : public GDecoratorItemPrivate
{
    Q_DECLARE_PUBLIC(GInverterItem)

public:
    GInverterItemPrivate();
    virtual ~GInverterItemPrivate();

public:
    virtual void onChildStatusChanged(GGhostItem *child) Q_DECL_FINAL;

public:
    virtual void executeChildItem() Q_DECL_FINAL;
};

#endif // GINVERTERITEM_P_H
