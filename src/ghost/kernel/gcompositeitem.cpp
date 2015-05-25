#include "gcompositeitem.h"
#include "gcompositeitem_p.h"

#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(qlcCompositeItem, "GtGhost.CompositeItem")

// class GCompositeItem

GCompositeItem::GCompositeItem(GCompositeItemPrivate &dd, QObject *parent)
    : GGhostItem(dd, parent)
{
}

void GCompositeItem::setUpdateMode(Ghost::UpdateMode mode)
{
    d_func()->updateMode = mode;
}

Ghost::UpdateMode GCompositeItem::updateMode() const
{
    return d_func()->updateMode;
}

// class GCompositeItemPrivate

GCompositeItemPrivate::GCompositeItemPrivate(LinearMode mode)
    : linearMode(mode)
    , updateMode(Ghost::ResetOnly)
    , seekIndex(-1)
{
}

GCompositeItemPrivate::~GCompositeItemPrivate()
{
}

bool GCompositeItemPrivate::initialize()
{
    if (childItems.isEmpty()) {
        qCWarning(qlcCompositeItem)
                << "Must have at least one child item.";
        return false;
    }

    updateChildItems();

    QListIterator<GGhostItem *> i(sortedChildItems());

    bool hasError = false;
    i.toBack();
    while (i.hasPrevious()) {
        GGhostItem *childItem = i.previous();
        if (!dptr(childItem)->initialize()) {
            hasError = true;
        }
    }
    if (hasError) {
        return hasError;
    }

    setStatus(Ghost::StandBy);

    return true;
}

void GCompositeItemPrivate::reset()
{
    Q_ASSERT(Ghost::Invalid != status);
    Q_ASSERT(Ghost::StandBy != status);
    Q_ASSERT(Ghost::Running != status);

    QListIterator<GGhostItem *> i(sortedChildItems());

    i.toBack();
    while (i.hasPrevious()) {
        GGhostItem *childItem = i.previous();
        if (dptr(childItem)->status != Ghost::StandBy) {
            dptr(childItem)->reset();
        }
    }

    updateChildItems();

    setStatus(Ghost::StandBy);
}

void GCompositeItemPrivate::execute()
{
    Q_ASSERT(Ghost::Invalid != status);
    Q_ASSERT(Ghost::Running != status);

    if ((Ghost::StandBy != status)
            && (updateMode == Ghost::Everytime)) {
        updateChildItems();
    }

    setStatus(Ghost::Running);

    seekIndex = -1;
    executeNextChildItem();
}

void GCompositeItemPrivate::terminate()
{
    Q_ASSERT(Ghost::Running == status);

    GGhostItemList &childItems = sortedChildItems();

    GGhostItem *childItem
            = childItems.at(seekIndex);
    dptr(childItem)->terminate();
}

void GCompositeItemPrivate::onChildStatusChanged(GGhostItem *child, Ghost::Status status)
{
    Q_UNUSED(child);

    if (Ghost::Invalid == this->status) {
        return;
    }

    if (Ghost::Stopped == status) {
        setStatus(status);
        return;
    }

    if (linearMode == Sequence) {
        if (Ghost::Success == status) {
            executeNextChildItem();
        } else if (Ghost::Failure == status) {
            setStatus(Ghost::Failure);
        }
    } else {
        if (Ghost::Failure == status) {
            executeNextChildItem();
        } else if (Ghost::Success == status) {
            setStatus(Ghost::Success);
        }
    }
}

void GCompositeItemPrivate::executeNextChildItem()
{
    GGhostItemList &childItems = sortedChildItems();

    bool r = false;
    int c = childItems.count();
    for (int i = seekIndex + 1; i < c; ++i) {
        GGhostItem *childItem = childItems.at(i);
        GGhostItemPrivate *childptr = dptr(childItem);
        if (childptr->callPrecondition()) {
            r = true;
            ++seekIndex;
            childptr->execute();
            break;
        }
    }

    if (false == r) {
        if (linearMode == Sequence) {
            setStatus(Ghost::Success);
        } else {
            setStatus(Ghost::Failure);
        }
    }
}
