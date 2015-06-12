#include "grepeaternode_p.h"
#include "grepeaternode_p_p.h"

#include <QtCore/QLoggingCategory>

#include "gghostevent.h"

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

void GRepeaterNodePrivate::confirmEvent(GGhostConfirmEvent *event)
{
    Q_CHECK_PTR(event->source());
    Q_ASSERT(event->source() == childNodes[0]);

    Ghost::Status sourceStatus = event->status();

    if (Ghost::Stopped == sourceStatus) {
        setStatus(Ghost::Stopped);
    } else if ((Ghost::Success == sourceStatus)
               || (Ghost::Failure == sourceStatus)) {
        if ((++loopCounter >= loopCount) && (0 != loopCount)) {
            setStatus(Ghost::Success);
            return;
        }

        GGhostNodePrivate *childptr = cast(childNodes[0]);
        if (childptr->callPrecondition()) {
            postExecuteEvent(childNodes[0]);
        } else {
            setStatus(breakStatus);
        }
    }
}
