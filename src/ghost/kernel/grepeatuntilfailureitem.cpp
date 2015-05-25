#include "grepeatuntilfailureitem.h"
#include "grepeatuntilfailureitem_p.h"

#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(qlcRepeatUntilFailureItem, "GtGhost.RepeatUntilFailureItem")

// class GRepeatUntilFailureItem

GRepeatUntilFailureItem::GRepeatUntilFailureItem(QObject *parent)
    : GDecoratorItem(*new GRepeatUntilFailureItemPrivate(), parent)
{
}

void GRepeatUntilFailureItem::setLoopCount(int value)
{
    Q_D(GRepeatUntilFailureItem);

    if (value < 0) {
        value = 0;
    }

    if (value != d->loopCount) {
        d->loopCount = value;
        emit loopCountChanged(value);
    }
}

int GRepeatUntilFailureItem::loopCount() const
{
    Q_D(const GRepeatUntilFailureItem);
    return d->loopCount;
}

// class GRepeatUntilFailureItemPrivate

GRepeatUntilFailureItemPrivate::GRepeatUntilFailureItemPrivate()
    : loopCount(0)
{
}

GRepeatUntilFailureItemPrivate::~GRepeatUntilFailureItemPrivate()
{
}

void GRepeatUntilFailureItemPrivate::onChildStatusChanged(GGhostItem *child, Ghost::Status status)
{
    Q_UNUSED(child);

    if (Ghost::Invalid == this->status) {
        return;
    }

    Q_CHECK_PTR(childItems[0]);
    Q_ASSERT(child == childItems[0]);

    if (Ghost::Success == status) {
        ++loopCounter;
        if (loopCount && (loopCounter == loopCount)) {
            setStatus(Ghost::Failure);
            return;
        }

        setFailureIfPreconditionFalse();
    } else if (Ghost::Failure == status) {
        setStatus(Ghost::Success);
    } else if (Ghost::Stopped == status) {
        setStatus(Ghost::Stopped);
    }
}

void GRepeatUntilFailureItemPrivate::executeChildItem()
{
    loopCounter = 0;

    setFailureIfPreconditionFalse();
}
