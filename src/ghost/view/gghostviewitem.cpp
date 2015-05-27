#include "gghostviewitem.h"
#include "gghostviewitem_p.h"

// class GGhostViewItem

GGhostViewItem::GGhostViewItem(QQuickItem *parent)
    : QQuickItem(*new GGhostViewItemPrivate(), parent)
{
}

void GGhostViewItem::setTarget(GGhostItem *value)
{
    Q_D(GGhostViewItem);

    if (d->target != value) {
        d->target = value;
        emit targetChanged(value);
    }
}

GGhostItem *GGhostViewItem::target() const
{
    Q_D(const GGhostViewItem);
    return d->target.data();
}

// class GGhostViewItemPrivate

GGhostViewItemPrivate::GGhostViewItemPrivate()
{
}

GGhostViewItemPrivate::~GGhostViewItemPrivate()
{
}
