#include "ginverternode_p.h"
#include "ginverternode_p_p.h"

// class GInverterNode

GInverterNode::GInverterNode(QObject *parent)
    : GDecoratorNode(*new GInverterNodePrivate(), parent)
{
}

// class GInverterNodePrivate

GInverterNodePrivate::GInverterNodePrivate()
    : GDecoratorNodePrivate(Ghost::InverterNode)
{
}

GInverterNodePrivate::~GInverterNodePrivate()
{
}

void GInverterNodePrivate::onChildStatusChanged(GGhostSourceNode *childNode)
{
    Q_ASSERT(Ghost::Invalid != status);

    Q_CHECK_PTR(childNodes[0]);
    Q_ASSERT(childNode == childNodes[0]);

    Ghost::Status childStatus = childNode->status();

    if (Ghost::Stopped == childStatus) {
        setStatus(Ghost::Stopped);
    } else if (Ghost::Success == childStatus) {
        setStatus(Ghost::Failure);
    } else if (Ghost::Failure == childStatus) {
        setStatus(Ghost::Success);
    }
}
