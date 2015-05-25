#ifndef GRANDOMSELECTORITEM_P_H
#define GRANDOMSELECTORITEM_P_H

#include "gcompositeitem_p.h"
#include "grandomselectoritem.h"

class GRandomSelectorItemPrivate : public GCompositeItemPrivate
{
    Q_DECLARE_PUBLIC(GRandomSelectorItem)

public:
    GRandomSelectorItemPrivate();
    virtual ~GRandomSelectorItemPrivate();

public:
    virtual void updateChildItems() Q_DECL_FINAL;
    virtual GGhostItemList &sortedChildItems() Q_DECL_FINAL;

private:
    Ghost::RandomMode randomMode;
    GGhostItemList randomChildItems;
};

#endif // GRANDOMSELECTORITEM_P_H
