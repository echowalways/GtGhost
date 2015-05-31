#include "gforcefailurenode_p.h"
#include "gforcefailurenode_p_p.h"

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

void GForceFailureNodePrivate::onChildStatusChanged(GGhostSourceNode *childNode)
{
    Q_ASSERT(Ghost::Invalid != status);

    Q_CHECK_PTR(childNodes[0]);
    Q_ASSERT(childNode == childNodes[0]);

    Ghost::Status childStatus = childNode->status();

    if (Ghost::Stopped == childStatus) {
        setStatus(Ghost::Stopped);
    } else if ((Ghost::Success == childStatus)
               || (Ghost::Failure == childStatus)) {
        setStatus(Ghost::Failure);
    }
}
