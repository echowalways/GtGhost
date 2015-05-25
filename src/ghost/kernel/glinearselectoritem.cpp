#include "glinearselectoritem.h"
#include "glinearselectoritem_p.h"

// class GLinearSelectorItem

GLinearSelectorItem::GLinearSelectorItem(QObject *parent)
    : GCompositeItem(*new GLinearSelectorItemPrivate(), parent)
{
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
