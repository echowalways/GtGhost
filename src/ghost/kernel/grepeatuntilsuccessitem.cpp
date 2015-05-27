#include "grepeatuntilsuccessitem.h"
#include "grepeatuntilsuccessitem_p.h"

#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(qlcRepeatUntilSuccessItem, "GtGhost.RepeatUntilSuccessItem")

// class GRepeatUntilSuccessItem

GRepeatUntilSuccessItem::GRepeatUntilSuccessItem(QObject *parent)
    : GDecoratorItem(*new GRepeatUntilSuccessItemPrivate(), parent)
{
}

Ghost::ItemType GRepeatUntilSuccessItem::itemType() const
{
    return Ghost::RepeatUntilSuccessItem;
}

void GRepeatUntilSuccessItem::setLoopCount(int value)
{
    Q_D(GRepeatUntilSuccessItem);

    if (value < 0) {
        value = 0;
    }

    if (value != d->loopCount) {
        d->loopCount = value;
        emit loopCountChanged(value);
    }
}

int GRepeatUntilSuccessItem::loopCount() const
{
    Q_D(const GRepeatUntilSuccessItem);
    return d->loopCount;
}

// class GRepeatUntilSuccessItemPrivate

GRepeatUntilSuccessItemPrivate::GRepeatUntilSuccessItemPrivate()
    : loopCount(0)
{
}

GRepeatUntilSuccessItemPrivate::~GRepeatUntilSuccessItemPrivate()
{
}

void GRepeatUntilSuccessItemPrivate::onChildStatusChanged(GGhostItem *child)
{
    if (Ghost::Invalid == status) {
        return;
    }

    Q_CHECK_PTR(childItems[0]);
    Q_ASSERT(child == childItems[0]);

    Ghost::Status childStatus = child->status();

    if (Ghost::Failure == childStatus) {
        ++loopCounter;
        if (loopCount && (loopCounter == loopCount)) {
            setStatus(Ghost::Failure);
            return;
        }

        setFailureIfPreconditionFalse();
    } else if (Ghost::Success == childStatus) {
        setStatus(Ghost::Success);
    } else if (Ghost::Stopped == childStatus) {
        setStatus(Ghost::Stopped);
    }
}

void GRepeatUntilSuccessItemPrivate::executeChildItem()
{
    loopCounter = 0;

    setFailureIfPreconditionFalse();
}
