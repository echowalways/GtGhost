#include "grepeatuntilfailurenode_p.h"
#include "grepeatuntilfailurenode_p_p.h"

#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(qlcRepeatUntilFailureNode, "GtGhost.RepeatUntilFailureNode")

// class GRepeatUntilFailureNode

GRepeatUntilFailureNode::GRepeatUntilFailureNode(QObject *parent)
    : GDecoratorNode(*new GRepeatUntilFailureNodePrivate(), parent)
{
}

void GRepeatUntilFailureNode::setLoopCount(int value)
{
    Q_D(GRepeatUntilFailureNode);

    if (value < 0) {
        qCWarning(qlcRepeatUntilFailureNode)
                << "Value is too small, reset to 0.";
        value = 0;
    }

    if (value != d->loopCount) {
        d->loopCount = value;
        emit loopCountChanged(value);
    }
}

int GRepeatUntilFailureNode::loopCount() const
{
    Q_D(const GRepeatUntilFailureNode);
    return d->loopCount;
}

// class GRepeatUntilFailureNodePrivate

GRepeatUntilFailureNodePrivate::GRepeatUntilFailureNodePrivate()
    : GDecoratorNodePrivate(Ghost::RepeatUntilFailureNode)
    , loopCount(0)
    , loopCounter(0)
{
}

GRepeatUntilFailureNodePrivate::~GRepeatUntilFailureNodePrivate()
{
}

void GRepeatUntilFailureNodePrivate::onChildStatusChanged(GGhostSourceNode *childNode)
{
    Q_ASSERT(Ghost::Invalid != status);

    Q_CHECK_PTR(childNodes[0]);
    Q_ASSERT(childNode == childNodes[0]);

    Ghost::Status childStatus = childNode->status();

    if (Ghost::Stopped == childStatus) {
        setStatus(Ghost::Stopped);
    } else if ((Ghost::Success == childStatus)
               || (Ghost::Failure == childStatus)) {
        if (Ghost::Failure == childStatus) {
            setStatus(Ghost::Success);
            return;
        }

        if ((++loopCounter >= loopCount) && (0 != loopCount)) {
            setStatus(Ghost::Failure);
            return;
        }

        GGhostNodePrivate *childptr = cast(childNodes[0]);
        if (childptr->callPrecondition()) {
            childptr->execute();
        } else {
            setStatus(breakStatus);
        }
    }
}
