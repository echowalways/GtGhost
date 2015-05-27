#include "grepeateritem.h"
#include "grepeateritem_p.h"

#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(qlcRepeaterItem, "GtGhost.RepeaterItem")

// class GRepeaterItem

GRepeaterItem::GRepeaterItem(QObject *parent)
    : GDecoratorItem(*new GRepeaterItemPrivate(), parent)
{
}

Ghost::ItemType GRepeaterItem::itemType() const
{
    return Ghost::RepeaterItem;
}

void GRepeaterItem::setLoopCount(int value)
{
    Q_D(GRepeaterItem);

    if (value < 0) {
        value = 0;
    }

    if (value != d->loopCount) {
        d->loopCount = value;
        emit loopCountChanged(value);
    }
}

int GRepeaterItem::loopCount() const
{
    Q_D(const GRepeaterItem);
    return d->loopCount;
}

// class GRepeaterItemPrivate

GRepeaterItemPrivate::GRepeaterItemPrivate()
    : loopCount(0)
{
}

GRepeaterItemPrivate::~GRepeaterItemPrivate()
{
}

void GRepeaterItemPrivate::onChildStatusChanged(GGhostItem *child)
{
    if (Ghost::Invalid == status) {
        return;
    }

    Q_CHECK_PTR(childItems[0]);
    Q_ASSERT(child == childItems[0]);

    Ghost::Status childStatus = child->status();

    if ((Ghost::Success == childStatus)
            || (Ghost::Failure == childStatus)) {
        ++loopCounter;
        if (loopCount && (loopCounter == loopCount)) {
            setStatus(Ghost::Success);
            return;
        }

        if (Ghost::Success == childStatus) {
            setFailureIfPreconditionFalse();
        } else if (Ghost::Failure == childStatus) {
            setFailureIfPreconditionFalse();
        }
    } else if (Ghost::Stopped == childStatus) {
        setStatus(Ghost::Stopped);
    }
}

void GRepeaterItemPrivate::executeChildItem()
{
    loopCounter = 0;

    setFailureIfPreconditionFalse();
}
