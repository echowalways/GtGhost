#ifndef GALWAYSFAILUREITEM_P_H
#define GALWAYSFAILUREITEM_P_H

#include "gdecoratoritem_p.h"
#include "galwaysfailureitem.h"

class GAlwaysFailureItemPrivate : public GDecoratorItemPrivate
{
    Q_DECLARE_PUBLIC(GAlwaysFailureItem)

public:
    GAlwaysFailureItemPrivate();
    virtual ~GAlwaysFailureItemPrivate();

public:
    virtual void onChildStatusChanged(GGhostItem *child, Ghost::Status status) Q_DECL_FINAL;

public:
    virtual void executeChildItem() Q_DECL_FINAL;
};

#endif // GALWAYSFAILUREITEM_P_H
