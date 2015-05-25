#ifndef GALWAYSSUCCESSITEM_P_H
#define GALWAYSSUCCESSITEM_P_H

#include "gdecoratoritem_p.h"
#include "galwayssuccessitem.h"

class GAlwaysSuccessItemPrivate : public GDecoratorItemPrivate
{
    Q_DECLARE_PUBLIC(GAlwaysSuccessItem)

public:
    GAlwaysSuccessItemPrivate();
    virtual ~GAlwaysSuccessItemPrivate();

public:
    virtual void onChildStatusChanged(GGhostItem *child, Ghost::Status status) Q_DECL_FINAL;

public:
    virtual void executeChildItem() Q_DECL_FINAL;
};

#endif // GALWAYSSUCCESSITEM_P_H
