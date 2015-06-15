#include "gforcesuccessnode_p.h"
#include "gforcesuccessnode_p_p.h"

#include "gghostevent.h"

// class GForceSuccessNode

/*!
    \qmltype ForceSuccessNode
    \instantiates GForceSuccessNode
    \inqmlmodule GtGhost
    \inherits DecoratorNode

    fff
 */

GForceSuccessNode::GForceSuccessNode(QObject *parent)
    : GDecoratorNode(*new GForceSuccessNodePrivate(), parent)
{
}

// class GForceSuccessNodePrivate

GForceSuccessNodePrivate::GForceSuccessNodePrivate()
    : GDecoratorNodePrivate(Ghost::ForceSuccessNode)
{
}

GForceSuccessNodePrivate::~GForceSuccessNodePrivate()
{
}

void GForceSuccessNodePrivate::confirmEvent(GGhostConfirmEvent *event)
{
    Q_CHECK_PTR(event->source());
    Q_ASSERT(event->source() == childNodes[0]);

    Ghost::Status childStatus = event->status();

    if (Ghost::Stopped == childStatus) {
        setStatus(Ghost::Stopped);
    } else if ((Ghost::Success == childStatus)
               || (Ghost::Failure == childStatus)) {
        setStatus(Ghost::Success);
    }
}
