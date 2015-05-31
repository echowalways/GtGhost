#include "grepeaternode_p.h"
#include "grepeaternode_p_p.h"

#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(qlcRepeaterNode, "GtGhost.RepeaterNode")

// class GRepeaterNode

GRepeaterNode::GRepeaterNode(QObject *parent)
    : GDecoratorNode(*new GRepeaterNodePrivate(), parent)
{
}

void GRepeaterNode::setLoopCount(int value)
{
    Q_D(GRepeaterNode);

    if (value < 0) {
        qCWarning(qlcRepeaterNode)
                << "Value is too small, reset to 0.";
        value = 0;
    }

    if (value != d->loopCount) {
        d->loopCount = value;
        emit loopCountChanged(value);
    }
}

int GRepeaterNode::loopCount() const
{
    Q_D(const GRepeaterNode);
    return d->loopCount;
}

// class GRepeaterNodePrivate

GRepeaterNodePrivate::GRepeaterNodePrivate()
    : GDecoratorNodePrivate(Ghost::RepeaterNode)
    , loopCount(0)
    , loopCounter(0)
{
}

GRepeaterNodePrivate::~GRepeaterNodePrivate()
{
}

void GRepeaterNodePrivate::onChildStatusChanged(GGhostSourceNode *childNode)
{
    Q_ASSERT(Ghost::Invalid != status);

    Q_CHECK_PTR(childNodes[0]);
    Q_ASSERT(childNode == childNodes[0]);

    Ghost::Status childStatus = childNode->status();

    if (Ghost::Stopped == childStatus) {
        setStatus(Ghost::Stopped);
    } else if ((Ghost::Success == childStatus)
               || (Ghost::Failure == childStatus)) {
        if ((++loopCounter >= loopCount) && (0 != loopCount)) {
            setStatus(Ghost::Success);
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
