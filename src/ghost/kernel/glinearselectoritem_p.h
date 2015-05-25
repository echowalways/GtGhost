#ifndef GLINEARSELECTORITEM_P_H
#define GLINEARSELECTORITEM_P_H

#include "gcompositeitem_p.h"
#include "glinearselectoritem.h"

class GLinearSelectorItemPrivate : public GCompositeItemPrivate
{
    Q_DECLARE_PUBLIC(GLinearSelectorItem)

public:
    GLinearSelectorItemPrivate();
    virtual ~GLinearSelectorItemPrivate();

public:
    virtual void updateChildItems() Q_DECL_FINAL;
    virtual GGhostItemList &sortedChildItems() Q_DECL_FINAL;
};

#endif // GLINEARSELECTORITEM_P_H
