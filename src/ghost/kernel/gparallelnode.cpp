#include "gparallelnode_p.h"
#include "gparallelnode_p_p.h"

// class GParallelNode

/*!
    \qmltype ParallelNode
    \instantiates GParallelNode
    \inqmlmodule GtGhost
    \inherits CompositeNode

    fff
 */

GParallelNode::GParallelNode(QObject *parent)
    : GCompositeNode(*new GParallelNodePrivate(), parent)
{
}

// class GParallelNodePrivate

GParallelNodePrivate::GParallelNodePrivate()
    : GCompositeNodePrivate(Ghost::ParallelNode)
    , executeState(false)
    , terminateState(false)
{
}

GParallelNodePrivate::~GParallelNodePrivate()
{
}

void GParallelNodePrivate::onChildStatusChanged(GGhostSourceNode *childNode)
{
    Q_UNUSED(childNode);
    Q_ASSERT(Ghost::Invalid != status);

    Ghost::Status childStatus = childNode->status();

    if ((Ghost::Success == childStatus)
            || (Ghost::Failure == childStatus)
            || (Ghost::Stopped == childStatus)) {
        if ((0 == --executeCounter) && !executeState) {
            if (terminateState) {
                setStatus(Ghost::Stopped);
            } else {
                setStatus(Ghost::Success);
            }
        }
    }
}

void GParallelNodePrivate::reset()
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

void GParallelNodePrivate::execute()
{
    Q_ASSERT(Ghost::Invalid != status);
    Q_ASSERT(Ghost::Running != status);

    setStatus(Ghost::Running);

    executeCounter = 0;
    executeState = false;
    terminateState = false;

    // executeAllChildNodes
    bool r = true;

    executeState = true;
    foreach (GGhostNode *childNode, childNodes) {
        GGhostNodePrivate *dptr = cast(childNode);
        if (dptr->callPrecondition()) {
            executeCounter += 1;
            dptr->execute();
            r = false;
        }
    }
    executeState = false;

    if (r) {
        setStatus(breakStatus);
    } else if (0 == executeCounter) {
        setStatus(Ghost::Success);
    }
}

void GParallelNodePrivate::terminate()
{
    Q_ASSERT(Ghost::Running == status);

    terminateState = true;
    foreach (GGhostNode *childNode, childNodes) {
        GGhostNodePrivate *dptr = cast(childNode);
        if (Ghost::Running == dptr->status) {
            dptr->terminate();
        }
    }
}
