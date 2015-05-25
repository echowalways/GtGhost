#ifndef GRANDOMSEQUENCEITEM_P_H
#define GRANDOMSEQUENCEITEM_P_H

#include "gcompositeitem_p.h"
#include "grandomsequenceitem.h"

class GRandomSequenceItemPrivate : public GCompositeItemPrivate
{
    Q_DECLARE_PUBLIC(GRandomSequenceItem)

public:
    GRandomSequenceItemPrivate();
    virtual ~GRandomSequenceItemPrivate();

public:
    virtual void updateChildItems() Q_DECL_FINAL;
    virtual GGhostItemList &sortedChildItems() Q_DECL_FINAL;

private:
    Ghost::RandomMode randomMode;
    GGhostItemList randomChildItems;
};

#endif // GRANDOMSEQUENCEITEM_P_H
