#include "gweightsequenceitem.h"
#include "gweightsequenceitem_p.h"

// class GWeightSequenceItem

GWeightSequenceItem::GWeightSequenceItem(QObject *parent)
    : GCompositeItem(*new GWeightSequenceItemPrivate(), parent)
{
}

Ghost::ItemType GWeightSequenceItem::itemType() const
{
    return Ghost::WeightSequenceItem;
}

// class GWeightSequenceItemPrivate

GWeightSequenceItemPrivate::GWeightSequenceItemPrivate()
    : GCompositeItemPrivate(Sequence)
{
}

GWeightSequenceItemPrivate::~GWeightSequenceItemPrivate()
{
}

void GWeightSequenceItemPrivate::updateChildItems()
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

GGhostItemList &GWeightSequenceItemPrivate::sortedChildItems()
{
    return weightChildItems;
}
