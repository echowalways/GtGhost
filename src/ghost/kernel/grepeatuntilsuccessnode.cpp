#include "grepeatuntilsuccessnode_p.h"
#include "grepeatuntilsuccessnode_p_p.h"

#include "gghostevents.h"

// class GRepeatUntilSuccessNode

GRepeatUntilSuccessNode::GRepeatUntilSuccessNode(QObject *parent)
    : GDecoratorNode(*new GRepeatUntilSuccessNodePrivate(), parent)
{
}

void GRepeatUntilSuccessNode::setLoopCount(int value)
{
    Q_D(GRepeatUntilSuccessNode);

    if (value < 0) {
        qWarning("GtGhost : Value is too small, reset to 0.");
        value = 0;
    }

    if (value != d->loopCount) {
        d->loopCount = value;
        emit loopCountChanged(value);
    }
}

int GRepeatUntilSuccessNode::loopCount() const
{
    Q_D(const GRepeatUntilSuccessNode);
    return d->loopCount;
}

// class GRepeatUntilSuccessNodePrivate

GRepeatUntilSuccessNodePrivate::GRepeatUntilSuccessNodePrivate()
    : GDecoratorNodePrivate(Ghost::RepeatUntilSuccessNode)
    , loopCount(0)
    , loopCounter(0)
{
}

GRepeatUntilSuccessNodePrivate::~GRepeatUntilSuccessNodePrivate()
{
}

void GRepeatUntilSuccessNodePrivate::confirmEvent(GGhostConfirmEvent *event)
{
    Q_CHECK_PTR(event->source());
    Q_ASSERT(event->source() == childNodes[0]);

    Ghost::Status sourceStatus = event->status();

    if (Ghost::Stopped == sourceStatus) {
        setStatus(Ghost::Stopped);
    } else if ((Ghost::Success == sourceStatus)
               || (Ghost::Failure == sourceStatus)) {
        if (Ghost::Success == sourceStatus) {
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
