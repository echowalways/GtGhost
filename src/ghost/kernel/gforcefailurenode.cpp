#include "gforcefailurenode_p.h"
#include "gforcefailurenode_p_p.h"

#include "gghostevent.h"

// class GForceFailureNode

GForceFailureNode::GForceFailureNode(QObject *parent)
    : GDecoratorNode(*new GForceFailureNodePrivate(), parent)
{
}

// class GForceFailureNodePrivate

GForceFailureNodePrivate::GForceFailureNodePrivate()
    : GDecoratorNodePrivate(Ghost::ForceFailureNode)
{
}

GForceFailureNodePrivate::~GForceFailureNodePrivate()
{
}

void GForceFailureNodePrivate::confirmEvent(GGhostConfirmEvent *event)
{
    Q_ASSERT(Ghost::Invalid != status);

    Ghost::Status childStatus = event->status();

    if (Ghost::Stopped == childStatus) {
        setStatus(Ghost::Stopped);
    } else if ((Ghost::Success == childStatus)
               || (Ghost::Failure == childStatus)) {
        setStatus(Ghost::Failure);
    }
}
