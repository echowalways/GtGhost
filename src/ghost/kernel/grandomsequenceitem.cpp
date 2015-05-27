#include "grandomsequenceitem.h"
#include "grandomsequenceitem_p.h"

// class GRandomSequenceItem

GRandomSequenceItem::GRandomSequenceItem(QObject *parent)
    : GCompositeItem(*new GRandomSequenceItemPrivate(), parent)
{
}

Ghost::ItemType GRandomSequenceItem::itemType() const
{
    return Ghost::RandomSequenceItem;
}

void GRandomSequenceItem::setRandomMode(Ghost::RandomMode mode)
{
    d_func()->randomMode = mode;
}

Ghost::RandomMode GRandomSequenceItem::randomMode() const
{
    return d_func()->randomMode;
}

// class GRandomSequenceItemPrivate

GRandomSequenceItemPrivate::GRandomSequenceItemPrivate()
    : GCompositeItemPrivate(Sequence)
{
}

GRandomSequenceItemPrivate::~GRandomSequenceItemPrivate()
{
}

void GRandomSequenceItemPrivate::updateChildItems()
{
    if (Ghost::Parity == randomMode) {
        Q_FOREACH (GGhostItem *childItem, childItems) {
            dptr(childItem)->orderedValue = qrand();
        }
    } else {
        Q_FOREACH (GGhostItem *childItem, childItems) {
            dptr(childItem)->orderedValue
                    = qrand() % dptr(childItem)->callWeight();
        }
    }

    if (randomChildItems.isEmpty()) {
        randomChildItems = childItems;
    }
    sort(randomChildItems);
}

GGhostItemList &GRandomSequenceItemPrivate::sortedChildItems()
{
    return randomChildItems;
}
