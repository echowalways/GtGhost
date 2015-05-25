#ifndef GLINEARSEQUENCEITEM_P_H
#define GLINEARSEQUENCEITEM_P_H

#include "gcompositeitem_p.h"
#include "glinearsequenceitem.h"

class GLinearSequenceItemPrivate : public GCompositeItemPrivate
{
    Q_DECLARE_PUBLIC(GLinearSequenceItem)

public:
    GLinearSequenceItemPrivate();
    virtual ~GLinearSequenceItemPrivate();

public:
    virtual void updateChildItems() Q_DECL_FINAL;
    virtual GGhostItemList &sortedChildItems() Q_DECL_FINAL;
};

#endif // GLINEARSEQUENCEITEM_P_H
