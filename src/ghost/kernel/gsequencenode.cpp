#include "gsequencenode_p.h"
#include "gsequencenode_p_p.h"

#include <QtDebug>

#include "gghostevent.h"

// class GSequenceNode

GSequenceNode::GSequenceNode(QObject *parent)
    : GCompositeNode(*new GSequenceNodePrivate(), parent)
{
}

// class GSequenceNodePrivate

GSequenceNodePrivate::GSequenceNodePrivate()
    : GCompositeNodePrivate(Ghost::SequenceNode)
{
}

GSequenceNodePrivate::~GSequenceNodePrivate()
{
}

void GSequenceNodePrivate::confirmEvent(GGhostConfirmEvent *event)
{
    Ghost::Status childStatus = event->status();

    if (Ghost::Stopped == childStatus) {
        setStatus(Ghost::Stopped);
    } else if (Ghost::Success == childStatus) {
        executeNextChildNode();
    } else if (Ghost::Failure == childStatus) {
        if (++unmatchCounter >= unmatchCount) {
            setStatus(Ghost::Failure);
        } else {
            executeNextChildNode();
        }
    }
}

void GSequenceNodePrivate::execute()
{
    Q_ASSERT(Ghost::Invalid != status);
    Q_ASSERT(Ghost::Running != status);

    setStatus(Ghost::Running);

    unmatchCounter = 0;
    executeIndex = -1;
    executeCounter = 0;

    executeNextChildNode();
}

void GSequenceNodePrivate::terminate()
{
    Q_ASSERT(Ghost::Running == status);

    GGhostNode *childNode
            = childNodes.at(executeIndex);
    cast(childNode)->terminate();
}

void GSequenceNodePrivate::executeNextChildNode()
{
    bool r = true;

    while (++executeIndex < childNodes.count()) {
        GGhostNode *childNode = childNodes.at(executeIndex);
        GGhostNodePrivate *dptr = cast(childNode);
        if (dptr->callPrecondition()) {
            ++executeCounter;
            postExecuteEvent(childNode);
            r = false;
            break;
        }
    }

    if (r) {
        if (executeCounter) {
            setStatus(Ghost::Success);
        } else {
            setStatus(breakStatus);
        }
    }
}
