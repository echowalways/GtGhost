#include "ginverternode_p.h"
#include "ginverternode_p_p.h"

#include "gghostevent.h"

// class GInverterNode

/*!
    \qmltype InverterNode
    \instantiates GInverterNode
    \inqmlmodule GtGhost
    \inherits DecoratorNode

    fff
 */

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

void GInverterNodePrivate::confirmEvent(GGhostConfirmEvent *event)
{
    Q_CHECK_PTR(event->source());
    Q_ASSERT(event->source() == childNodes[0]);

    Ghost::Status sourceStatus = event->status();

    if (Ghost::Stopped == sourceStatus) {
        setStatus(Ghost::Stopped);
    } else if (Ghost::Success == sourceStatus) {
        setStatus(Ghost::Failure);
    } else if (Ghost::Failure == sourceStatus) {
        setStatus(Ghost::Success);
    }
}
