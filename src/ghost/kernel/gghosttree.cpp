#include "gghosttree.h"
#include "gghosttree_p.h"

#include <QtCore/QDateTime>
#include <QtCore/QLoggingCategory>

#include "gghostitem.h"
#include "gghostitem_p.h"

Q_LOGGING_CATEGORY(qlcGhostTree, "GtGhost.GhostTree")

// class GGhostTree

GGhostTree::GGhostTree(QObject *parent)
    : GGhostNode(*new GGhostTreePrivate(), parent)
{
}

void GGhostTree::classBegin()
{
    Q_D(GGhostTree);

    qsrand(QDateTime::currentMSecsSinceEpoch());

    d->parentTree = this;
}

void GGhostTree::componentComplete()
{
    Q_D(GGhostTree);

    Q_FOREACH (GGhostItem *childItem, d->childItems) {
        GGhostItemPrivate *childptr
                = GGhostItemPrivate::dptr(childItem);
        childptr->sync(this, this);
    }

    if (d->initialize()) {
        d->setStatus(Ghost::StandBy);
    }
}

void GGhostTree::start()
{
    Q_D(GGhostTree);

    if ((Ghost::Invalid != d->status)
            && (Ghost::Running != d->status)) {
        d->execute();
    }
}

void GGhostTree::stop()
{
    Q_D(GGhostTree);

    if (Ghost::Running == d->status) {
        d->terminate();
    }
}

void GGhostTree::reset()
{
    Q_D(GGhostTree);

    if ((Ghost::Success == d->status)
            || (Ghost::Failure == d->status)
            || (Ghost::Stopped == d->status)) {
        d->reset();
    }
}

void GGhostTree::set(const QString &key, const QJSValue &value)
{
    Q_D(GGhostTree);

    if (value.isUndefined()) {
        d->runtimeVariables.remove(key);
    } else {
        d->runtimeVariables.insert(key, value);
    }
}

QJSValue GGhostTree::get(const QString &key) const
{
    Q_D(const GGhostTree);
    return d->runtimeVariables.value(key);
}

// class GGhostTreePrivate

GGhostTreePrivate::GGhostTreePrivate()
{
}

GGhostTreePrivate::~GGhostTreePrivate()
{
}

GGhostItemPrivate *GGhostTreePrivate::dptr(GGhostItem *item)
{
    return GGhostItemPrivate::dptr(item);
}

const GGhostItemPrivate *GGhostTreePrivate::dptr(const GGhostItem *item)
{
    return GGhostItemPrivate::dptr(item);
}

bool GGhostTreePrivate::initialize()
{
    if (childItems.count() != 1) {
        qDebug(qlcGhostTree)
                << "Allows only one child node.";
        return false;
    }

    bool hasError = false;
    Q_FOREACH (GGhostItem *childItem, childItems) {
        GGhostItemPrivate *childptr
                = GGhostItemPrivate::dptr(childItem);
        if (!childptr->initialize()) {
            hasError = true;
        }
    }
    return !hasError;
}

void GGhostTreePrivate::reset()
{
    Q_CHECK_PTR(childItems[0]);
    Q_ASSERT(Ghost::Invalid != status);
    Q_ASSERT(Ghost::StandBy != status);
    Q_ASSERT(Ghost::Running != status);

    dptr(childItems[0])->reset();
    runtimeVariables.clear();

    setStatus(Ghost::StandBy);
}

void GGhostTreePrivate::execute()
{
    Q_CHECK_PTR(childItems[0]);
    Q_ASSERT(Ghost::Invalid != status);
    Q_ASSERT(Ghost::Running != status);

    setStatus(Ghost::Running);

    GGhostItemPrivate *rootptr = dptr(childItems[0]);
    if (rootptr->callPrecondition()) {
        rootptr->execute();
    } else {
        setStatus(Ghost::Failure);
    }
}

void GGhostTreePrivate::terminate()
{
    Q_CHECK_PTR(childItems[0]);
    Q_ASSERT(Ghost::Running == status);

    dptr(childItems[0])->terminate();
}

void GGhostTreePrivate::onStatusChanged()
{
    Q_Q(GGhostTree);

    switch (status) {
    case Ghost::Invalid:
    case Ghost::StandBy:
        break;
    case Ghost::Running:
        emit q->started();
        break;
    case Ghost::Success:
    case Ghost::Failure:
        emit q->finished();
        // pass through
    case Ghost::Stopped:
        emit q->stopped();
        break;
    }
}

void GGhostTreePrivate::onChildStatusChanged(GGhostItem *child)
{
    if (Ghost::Invalid == status) {
        return;
    }

    Q_CHECK_PTR(childItems[0]);
    Q_ASSERT(child == childItems[0]);

    Ghost::Status childStatus = child->status();

    if ((Ghost::Success == childStatus)
            || (Ghost::Failure == childStatus)
            || (Ghost::Stopped == childStatus)) {
        setStatus(childStatus);
    }
}
