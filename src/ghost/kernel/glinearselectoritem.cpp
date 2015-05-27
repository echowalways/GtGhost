#include "glinearselectoritem.h"
#include "glinearselectoritem_p.h"

// class GLinearSelectorItem

GLinearSelectorItem::GLinearSelectorItem(QObject *parent)
    : GCompositeItem(*new GLinearSelectorItemPrivate(), parent)
{
}

Ghost::ItemType GLinearSelectorItem::itemType() const
{
    return Ghost::LinearSelectorItem;
}

// class GLinearSelectorItemPrivate

GLinearSelectorItemPrivate::GLinearSelectorItemPrivate()
    : GCompositeItemPrivate(Selector)
{
}

GLinearSelectorItemPrivate::~GLinearSelectorItemPrivate()
{
}

void GLinearSelectorItemPrivate::updateChildItems()
{
}

GGhostItemList &GLinearSelectorItemPrivate::sortedChildItems()
{
    return childItems;
}
