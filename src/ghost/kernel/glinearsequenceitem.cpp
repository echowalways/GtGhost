#include "glinearsequenceitem.h"
#include "glinearsequenceitem_p.h"

// class GLinearSequenceItem

GLinearSequenceItem::GLinearSequenceItem(QObject *parent)
    : GCompositeItem(*new GLinearSequenceItemPrivate(), parent)
{
}

// class GLinearSequenceItemPrivate

GLinearSequenceItemPrivate::GLinearSequenceItemPrivate()
    : GCompositeItemPrivate(Sequence)
{
}

GLinearSequenceItemPrivate::~GLinearSequenceItemPrivate()
{
}

void GLinearSequenceItemPrivate::updateChildItems()
{
}

GGhostItemList &GLinearSequenceItemPrivate::sortedChildItems()
{
    return childItems;
}
