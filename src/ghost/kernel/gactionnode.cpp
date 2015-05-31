#include "gactionnode_p.h"
#include "gactionnode_p_p.h"

// class GActionNode

GActionNode::GActionNode(QObject *parent)
    : GLeafNode(*new GActionNodePrivate(), parent)
{
}

void GActionNode::setSuccessStatus()
{
    Q_D(GActionNode);
    d->setStatus(Ghost::Success);
}

void GActionNode::setFailureStatus()
{
    Q_D(GActionNode);
    d->setStatus(Ghost::Failure);
}

void GActionNode::setStoppedStatus()
{
    Q_D(GActionNode);
    d->setStatus(Ghost::Stopped);
}


// class GActionNodePrivate

GActionNodePrivate::GActionNodePrivate()
    : GLeafNodePrivate(Ghost::ActionNode)
{
}

GActionNodePrivate::~GActionNodePrivate()
{
}

void GActionNodePrivate::reset()
{
    Q_Q(GActionNode);

    Q_ASSERT(Ghost::Invalid != status);
    Q_ASSERT(Ghost::StandBy != status);
    Q_ASSERT(Ghost::Running != status);

    emit q->reset();

    setStatus(Ghost::StandBy);
}

void GActionNodePrivate::execute()
{
    Q_Q(GActionNode);

    Q_ASSERT(Ghost::Invalid != status);
    Q_ASSERT(Ghost::Running != status);

    setStatus(Ghost::Running);

    emit q->execute();
}

void GActionNodePrivate::terminate()
{
    Q_Q(GActionNode);

    Q_ASSERT(Ghost::Running == status);

    emit q->terminate();
}
