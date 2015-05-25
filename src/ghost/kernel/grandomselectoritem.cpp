#include "grandomselectoritem.h"
#include "grandomselectoritem_p.h"

// class GRandomSelectorItem

GRandomSelectorItem::GRandomSelectorItem(QObject *parent)
    : GCompositeItem(*new GRandomSelectorItemPrivate(), parent)
{
}

void GRandomSelectorItem::setRandomMode(Ghost::RandomMode mode)
{
    d_func()->randomMode = mode;
}

Ghost::RandomMode GRandomSelectorItem::randomMode() const
{
    return d_func()->randomMode;
}

// class GRandomSelectorItemPrivate

GRandomSelectorItemPrivate::GRandomSelectorItemPrivate()
    : GCompositeItemPrivate(Selector)
{
}

GRandomSelectorItemPrivate::~GRandomSelectorItemPrivate()
{
}

void GRandomSelectorItemPrivate::updateChildItems()
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

GGhostItemList &GRandomSelectorItemPrivate::sortedChildItems()
{
    return randomChildItems;
}
