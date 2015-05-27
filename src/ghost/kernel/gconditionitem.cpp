#include "gconditionitem.h"
#include "gconditionitem_p.h"

#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(qlcConditionItem, "GtGhost.ConditionItem")

// class GConditionItem

GConditionItem::GConditionItem(QObject *parent)
    : GGhostItem(*new GConditionItemPrivate(), parent)
{
}

Ghost::NodeType GConditionItem::nodeType() const
{
    return Ghost::ConditionNode;
}

Ghost::ItemType GConditionItem::itemType() const
{
    return Ghost::ConditionItem;
}

void GConditionItem::setCondition(const QJSValue &value)
{
    Q_D(GConditionItem);

    if (!d->condition.equals(value)) {
        d->condition = value;
        emit conditionChanged(value);
    }
}

QJSValue GConditionItem::condition() const
{
    Q_D(const GConditionItem);
    return d->condition;
}

// class GConditionItemPrivate

GConditionItemPrivate::GConditionItemPrivate()
{
}

GConditionItemPrivate::~GConditionItemPrivate()
{
}

bool GConditionItemPrivate::initialize()
{
    if (!childItems.isEmpty()) {
        qCWarning(qlcConditionItem)
                << "Does not allow child items.";
        return false;
    }

    setStatus(Ghost::StandBy);

    return true;
}

void GConditionItemPrivate::reset()
{
    Q_ASSERT(Ghost::Invalid != status);
    Q_ASSERT(Ghost::StandBy != status);
    Q_ASSERT(Ghost::Running != status);

    emit q_func()->reset();

    setStatus(Ghost::StandBy);
}

void GConditionItemPrivate::execute()
{
    Q_ASSERT(Ghost::Invalid != status);
    Q_ASSERT(Ghost::Running != status);

    setStatus(Ghost::Running);

    if (callCondition()) {
        setStatus(Ghost::Success);
    } else {
        setStatus(Ghost::Failure);
    }
}

void GConditionItemPrivate::terminate()
{
    Q_ASSERT(Ghost::Running == status);
}

bool GConditionItemPrivate::callCondition()
{
    QJSValue value = condition;

    if (condition.isCallable()) {
        value = condition.call();
    }

    if (value.isBool()) {
        return value.toBool();
    } else if (value.isError()) {
        // error
    }

    return false;
}
