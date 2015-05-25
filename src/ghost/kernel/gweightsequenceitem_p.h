#ifndef GWEIGHTSEQUENCEITEM_P_H
#define GWEIGHTSEQUENCEITEM_P_H

#include "gcompositeitem_p.h"
#include "gweightsequenceitem.h"

class GWeightSequenceItemPrivate : public GCompositeItemPrivate
{
    Q_DECLARE_PUBLIC(GWeightSequenceItem)

public:
    GWeightSequenceItemPrivate();
    virtual ~GWeightSequenceItemPrivate();

public:
    virtual void updateChildItems() Q_DECL_FINAL;
    virtual GGhostItemList &sortedChildItems() Q_DECL_FINAL;

private:
    GGhostItemList weightChildItems;
};

#endif // GWEIGHTSEQUENCEITEM_P_H
