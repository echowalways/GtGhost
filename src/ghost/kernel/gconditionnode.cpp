#include "gconditionnode_p.h"
#include "gconditionnode_p_p.h"

// class GConditionNode

GConditionNode::GConditionNode(QObject *parent)
    : GLeafNode(*new GConditionNodePrivate(), parent)
{
    connect(this, &GGhostSourceNode::statusChanged,
            this, &GConditionNode::onStatusChanged);
}

void GConditionNode::setCondition(const QJSValue &value)
{
    Q_D(GConditionNode);

    if (!d->condition.equals(value)) {
        d->condition = value;
        emit conditionChanged(value);
    }
}

QJSValue GConditionNode::condition() const
{
    Q_D(const GConditionNode);
    return d->condition;
}

void GConditionNode::onStatusChanged(Ghost::Status status)
{
    if (Ghost::Success == status) {
        emit passed();
    } else if (Ghost::Failure == status) {
        emit unpassed();
    }
}

// class GConditionNodePrivate

GConditionNodePrivate::GConditionNodePrivate()
    : GLeafNodePrivate(Ghost::ConditionNode)
{
}

GConditionNodePrivate::~GConditionNodePrivate()
{
}

void GConditionNodePrivate::reset()
{
    Q_ASSERT(Ghost::Invalid != status);
    Q_ASSERT(Ghost::StandBy != status);
    Q_ASSERT(Ghost::Running != status);

    setStatus(Ghost::StandBy);
}

void GConditionNodePrivate::execute()
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

void GConditionNodePrivate::terminate()
{
    Q_ASSERT(Ghost::Running == status);
}

bool GConditionNodePrivate::callCondition()
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
