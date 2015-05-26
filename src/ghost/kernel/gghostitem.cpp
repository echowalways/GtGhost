#include "gghostitem.h"
#include "gghostitem_p.h"

#include <QtCore/QLoggingCategory>

#include "gghosttree.h"
#include "gghosttree_p.h"

Q_LOGGING_CATEGORY(qlcGhostItem, "GtGhost.GhostItem")

// class GGhostItem

GGhostItem::GGhostItem(GGhostItemPrivate &dd, QObject *parent)
    : GGhostNode(dd, parent)
{
}

void GGhostItem::classBegin()
{
}

void GGhostItem::componentComplete()
{
}

GGhostTree *GGhostItem::parentTree() const
{
    Q_D(const GGhostNode);
    return d->parentTree;
}

GGhostItem *GGhostItem::parentItem() const
{
    Q_D(const GGhostNode);
    return qobject_cast<GGhostItem *>(d->parentNode);
}

void GGhostItem::set(const QString &key, const QJSValue &value)
{
    Q_D(GGhostItem);

    if (d->parentTree) {
        d->parentTree->set(key, value);
    }
}

QJSValue GGhostItem::get(const QString &key) const
{
    Q_D(const GGhostItem);

    if (d->parentTree) {
        return d->parentTree->get(key);
    }

    return QJSValue();
}

void GGhostItem::setPrecondition(const QJSValue &value)
{
    Q_D(GGhostItem);

    if (!d->precondition.equals(value)) {
        d->precondition = value;
        emit preconditionChanged(value);
    }
}

void GGhostItem::setWeight(const QJSValue &value)
{
    Q_D(GGhostItem);

    if (!d->weight.equals(value)) {
        d->weight = value;
        emit weightChanged(value);
    }
}

QJSValue GGhostItem::precondition() const
{
    Q_D(const GGhostItem);
    return d->precondition;
}

QJSValue GGhostItem::weight() const
{
    Q_D(const GGhostItem);
    return d->weight;
}

// class GGhostItemPrivate

GGhostItemPrivate::GGhostItemPrivate()
    : orderedValue(0)
{
}

GGhostItemPrivate::~GGhostItemPrivate()
{
}

void GGhostItemPrivate::sync(GGhostTree *parentTree, GGhostNode *parentNode)
{
    this->parentTree = parentTree;
    this->parentNode = parentNode;

    Q_FOREACH (GGhostItem *childItem, childItems) {
        auto childptr = GGhostItemPrivate::dptr(childItem);
        childptr->sync(parentTree, q_func());
    }
}

bool GGhostItemPrivate::callPrecondition()
{
    if (precondition.isUndefined()) {
        return true;
    }

    QJSValue value = precondition;

    if (precondition.isCallable()) {
        value = precondition.call();
    }

    if (value.isBool()) {
        return value.toBool();
    } else if (value.isError()) {
        // error
    }

    return false;
}

uint GGhostItemPrivate::callWeight()
{
    if (weight.isUndefined()) {
        return 1u;
    }

    QJSValue value = weight;

    if (weight.isCallable()) {
        value = weight.call();
    }

    if (value.isNumber()) {
        return qMax(value.toUInt(), 1u);
    } else if (value.isError()) {
        // error
    }

    return 1u;
}

void GGhostItemPrivate::sort(GGhostItemList &items)
{
    qSort(items.begin(), items.end(), &GGhostItemPrivate::itemGreatThan);
}

bool GGhostItemPrivate::itemGreatThan(GGhostItem *lhs, GGhostItem *rhs)
{
    return lhs->d_func()->orderedValue > rhs->d_func()->orderedValue;
}
