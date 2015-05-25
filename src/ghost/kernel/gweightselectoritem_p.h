#ifndef GWEIGHTSELECTORITEM_P_H
#define GWEIGHTSELECTORITEM_P_H

#include "gcompositeitem_p.h"
#include "gweightselectoritem.h"

class GWeightSelectorItemPrivate : public GCompositeItemPrivate
{
    Q_DECLARE_PUBLIC(GWeightSelectorItem)

public:
    GWeightSelectorItemPrivate();
    virtual ~GWeightSelectorItemPrivate();

public:
    virtual void updateChildItems() Q_DECL_FINAL;
    virtual GGhostItemList &sortedChildItems() Q_DECL_FINAL;

private:
    GGhostItemList weightChildItems;
};

#endif // GWEIGHTSELECTORITEM_P_H
