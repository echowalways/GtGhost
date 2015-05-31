#include "gforcesuccessnode_p.h"
#include "gforcesuccessnode_p_p.h"

// class GForceSuccessNode

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

void GForceSuccessNodePrivate::onChildStatusChanged(GGhostSourceNode *childNode)
{
    Q_ASSERT(Ghost::Invalid != status);

    Q_CHECK_PTR(childNodes[0]);
    Q_ASSERT(childNode == childNodes[0]);

    Ghost::Status childStatus = childNode->status();

    if (Ghost::Stopped == childStatus) {
        setStatus(Ghost::Stopped);
    } else if ((Ghost::Success == childStatus)
               || (Ghost::Failure == childStatus)) {
        setStatus(Ghost::Success);
    }
}
