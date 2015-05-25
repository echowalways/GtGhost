#include "ginverteritem.h"
#include "ginverteritem_p.h"

#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(qlcInverterItem, "GtGhost.InverterItem")

// class GInverterItem

GInverterItem::GInverterItem(QObject *parent)
    : GDecoratorItem(*new GInverterItemPrivate(), parent)
{
}

// class GInverterItemPrivate

GInverterItemPrivate::GInverterItemPrivate()
{
}

GInverterItemPrivate::~GInverterItemPrivate()
{
}

void GInverterItemPrivate::onChildStatusChanged(GGhostItem *child, Ghost::Status status)
{
    Q_UNUSED(child);

    if (Ghost::Invalid == this->status) {
        return;
    }

    Q_CHECK_PTR(childItems[0]);
    Q_ASSERT(child == childItems[0]);

    if (Ghost::Stopped == status) {
        setStatus(Ghost::Stopped);
    } else if (Ghost::Success == status) {
        setStatus(Ghost::Failure);
    } else if (Ghost::Failure == status) {
        setStatus(Ghost::Success);
    }
}

void GInverterItemPrivate::executeChildItem()
{
    setSuccessIfPreconditionFalse();
}
