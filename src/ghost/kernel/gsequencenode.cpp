#include "gsequencenode_p.h"
#include "gsequencenode_p_p.h"

// class GSequenceNode

/*!
    \qmltype SequenceNode
    \instantiates GSequenceNode
    \inqmlmodule GtGhost
    \inherits CompositeNode

    fff
 */

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

void GSequenceNodePrivate::onChildStatusChanged(GGhostSourceNode *childNode)
{
    Q_ASSERT(Ghost::Invalid != status);

    Ghost::Status childStatus = childNode->status();

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

void GSequenceNodePrivate::reset()
{
    Q_ASSERT(Ghost::Invalid != status);
    Q_ASSERT(Ghost::StandBy != status);
    Q_ASSERT(Ghost::Running != status);

    QListIterator<GGhostNode *> i(childNodes);

    i.toBack();
    while (i.hasPrevious()) {
        GGhostNode *childNode = i.previous();
        if (Ghost::StandBy != cast(childNode)->status) {
            cast(childNode)->reset();
        }
    }

    setStatus(Ghost::StandBy);
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
            dptr->execute();
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
