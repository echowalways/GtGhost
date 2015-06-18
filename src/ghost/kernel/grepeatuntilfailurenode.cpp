#include "grepeatuntilfailurenode_p.h"
#include "grepeatuntilfailurenode_p_p.h"

#include "gghostevents.h"

// class GRepeatUntilFailureNode

GRepeatUntilFailureNode::GRepeatUntilFailureNode(QObject *parent)
    : GDecoratorNode(*new GRepeatUntilFailureNodePrivate(), parent)
{
}

void GRepeatUntilFailureNode::setLoopCount(int value)
{
    Q_D(GRepeatUntilFailureNode);

    if (value < 0) {
        qWarning("GtGhost : Value is too small, reset to 0.");
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

void GRepeatUntilFailureNodePrivate::confirmEvent(GGhostConfirmEvent *event)
{
    Q_CHECK_PTR(event->source());
    Q_ASSERT(event->source() == childNodes[0]);

    Ghost::Status sourceStatus = event->status();

    if (Ghost::Stopped == sourceStatus) {
        setStatus(Ghost::Stopped);
    } else if ((Ghost::Success == sourceStatus)
               || (Ghost::Failure == sourceStatus)) {
        if (Ghost::Failure == sourceStatus) {
            setStatus(Ghost::Success);
            return;
        }

        if ((++loopCounter >= loopCount) && (0 != loopCount)) {
            setStatus(Ghost::Failure);
            return;
        }

        GGhostNodePrivate *childptr = cast(childNodes[0]);
        if (childptr->callPrecondition()) {
            postExecuteEvent(childNodes[0]);
        } else {
            setStatus(brokenStatus);
        }
    }
}
