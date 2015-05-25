#include "glinearcompositeitem.h"
#include "glinearcompositeitem_p.h"

#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(qlcLinearCompositeItem, "GtGhost.LinearCompositeItem")

// class GLinearCompositeItem

GLinearCompositeItem::GLinearCompositeItem(GLinearCompositeItemPrivate &dd, QObject *parent)
    : GGhostItem(dd, parent)
{
}

void GLinearCompositeItem::setUpdateMode(GLinearCompositeItem::UpdateMode mode)
{
    d_func()->updateMode = mode;
}

GLinearCompositeItem::UpdateMode GLinearCompositeItem::updateMode() const
{
    return d_func()->updateMode;
}

// class GLinearCompositeItemPrivate

GLinearCompositeItemPrivate::GLinearCompositeItemPrivate(LinearMode mode)
    : linearMode(mode)
    , updateMode(GLinearCompositeItem::ResetOnly)
    , seekIndex(-1)
{
}

GLinearCompositeItemPrivate::~GLinearCompositeItemPrivate()
{
}

void GLinearCompositeItemPrivate::onChildStatusChanged(GGhostItem *childItem, GGhostNode::Status status)
{
    Q_UNUSED(childItem);

    if (GGhostItem::Invalid == this->status) {
        return;
    }

    if (GGhostItem::Stopped == status) {
        setStatus(status);
        return;
    }

    if (linearMode == Sequence) {
        if (GGhostItem::Success == status) {
            executeNextChildItem();
        } else if (GGhostItem::Failure == status) {
            setStatus(GGhostItem::Failure);
        }
    } else {
        if (GGhostItem::Failure == status) {
            executeNextChildItem();
        } else if (GGhostItem::Success == status) {
            setStatus(GGhostItem::Success);
        }
    }
}

bool GLinearCompositeItemPrivate::initialize()
{
    if (childItems.isEmpty()) {
        qCWarning(qlcLinearCompositeItem)
                << "Must have at least one child item.";
        return false;
    }

    updateChildItems();

    QListIterator<GGhostItem *> i(sortedChildItems());

    bool hasError = false;
    i.toBack();
    while (i.hasPrevious()) {
        GGhostItem *childItem = i.previous();
        if (!get(childItem)->initialize()) {
            hasError = true;
        }
    }
    if (hasError) {
        return hasError;
    }

    setStatus(GGhostItem::StandBy);

    return true;
}

void GLinearCompositeItemPrivate::reset()
{
    Q_ASSERT(GGhostItem::Invalid != status);
    Q_ASSERT(GGhostItem::StandBy != status);
    Q_ASSERT(GGhostItem::Running != status);

    QListIterator<GGhostItem *> i(sortedChildItems());

    i.toBack();
    while (i.hasPrevious()) {
        GGhostItem *childItem = i.previous();
        if (get(childItem)->status != GGhostItem::StandBy) {
            get(childItem)->reset();
        }
    }

    updateChildItems();

    setStatus(GGhostItem::StandBy);
}

void GLinearCompositeItemPrivate::execute()
{
    Q_ASSERT(GGhostItem::Invalid != status);
    Q_ASSERT(GGhostItem::Running != status);

    if ((GGhostItem::StandBy != status)
            && (updateMode == GLinearCompositeItem::Everytime)) {
        updateChildItems();
    }

    setStatus(GGhostItem::Running);

    seekIndex = -1;
    executeNextChildItem();
}

void GLinearCompositeItemPrivate::terminate()
{
    Q_ASSERT(GGhostItem::Running == status);

    GGhostItemList &childItems = sortedChildItems();

    GGhostItem *childItem
            = childItems.at(seekIndex);
    get(childItem)->terminate();
}

void GLinearCompositeItemPrivate::executeNextChildItem()
{
    GGhostItemList &childItems = sortedChildItems();

    bool r = false;
    int c = childItems.count();
    for (int i = seekIndex + 1; i < c; ++i) {
        GGhostItem *childItem = childItems.at(i);
        GGhostItemPrivate *childptr = get(childItem);
        if (childptr->callPrecondition()) {
            r = true;
            ++seekIndex;
            childptr->execute();
            break;
        }
    }

    if (false == r) {
        if (linearMode == Sequence) {
            setStatus(GGhostItem::Success);
        } else {
            setStatus(GGhostItem::Failure);
        }
    }
}
