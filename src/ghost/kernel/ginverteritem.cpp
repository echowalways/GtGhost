#include "ginverteritem.h"
#include "ginverteritem_p.h"

#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(qlcInverterItem, "GtGhost.InverterItem")

// class GInverterItem

GInverterItem::GInverterItem(QObject *parent)
    : GDecoratorItem(*new GInverterItemPrivate(), parent)
{
}

Ghost::ItemType GInverterItem::itemType() const
{
    return Ghost::InverterItem;
}

// class GInverterItemPrivate

GInverterItemPrivate::GInverterItemPrivate()
{
}

GInverterItemPrivate::~GInverterItemPrivate()
{
}

void GInverterItemPrivate::onChildStatusChanged(GGhostItem *child)
{
    if (Ghost::Invalid == status) {
        return;
    }

    Q_CHECK_PTR(childItems[0]);
    Q_ASSERT(child == childItems[0]);

    Ghost::Status childStatus = child->status();

    if (Ghost::Stopped == childStatus) {
        setStatus(Ghost::Stopped);
    } else if (Ghost::Success == childStatus) {
        setStatus(Ghost::Failure);
    } else if (Ghost::Failure == childStatus) {
        setStatus(Ghost::Success);
    }
}

void GInverterItemPrivate::executeChildItem()
{
    setSuccessIfPreconditionFalse();
}
