#include "gweightselectoritem.h"
#include "gweightselectoritem_p.h"

// class GWeightSelectorItem

GWeightSelectorItem::GWeightSelectorItem(QObject *parent)
    : GCompositeItem(*new GWeightSelectorItemPrivate(), parent)
{
}

// class GWeightSelectorItemPrivate

GWeightSelectorItemPrivate::GWeightSelectorItemPrivate()
    : GCompositeItemPrivate(Selector)
{
}

GWeightSelectorItemPrivate::~GWeightSelectorItemPrivate()
{
}

void GWeightSelectorItemPrivate::updateChildItems()
{
    Q_FOREACH (GGhostItem *childItem, childItems) {
        dptr(childItem)->orderedValue
                = dptr(childItem)->callWeight();
    }

    if (weightChildItems.isEmpty()) {
        weightChildItems = childItems;
    }
    sort(weightChildItems);
}

GGhostItemList &GWeightSelectorItemPrivate::sortedChildItems()
{
    return weightChildItems;
}
