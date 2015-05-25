#include "grepeatuntilsuccessitem.h"
#include "grepeatuntilsuccessitem_p.h"

#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(qlcRepeatUntilSuccessItem, "GtGhost.RepeatUntilSuccessItem")

// class GRepeatUntilSuccessItem

GRepeatUntilSuccessItem::GRepeatUntilSuccessItem(QObject *parent)
    : GDecoratorItem(*new GRepeatUntilSuccessItemPrivate(), parent)
{
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

void GRepeatUntilSuccessItemPrivate::onChildStatusChanged(GGhostItem *child, Ghost::Status status)
{
    Q_UNUSED(child);

    if (Ghost::Invalid == this->status) {
        return;
    }

    Q_CHECK_PTR(childItems[0]);
    Q_ASSERT(child == childItems[0]);

    if (Ghost::Failure == status) {
        ++loopCounter;
        if (loopCount && (loopCounter == loopCount)) {
            setStatus(Ghost::Failure);
            return;
        }

        setFailureIfPreconditionFalse();
    } else if (Ghost::Success == status) {
        setStatus(Ghost::Success);
    } else if (Ghost::Stopped == status) {
        setStatus(Ghost::Stopped);
    }
}

void GRepeatUntilSuccessItemPrivate::executeChildItem()
{
    loopCounter = 0;

    setFailureIfPreconditionFalse();
}
