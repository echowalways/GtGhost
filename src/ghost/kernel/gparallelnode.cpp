#include "gparallelnode_p.h"
#include "gparallelnode_p_p.h"

#include "gghostevent.h"

// class GParallelNode

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

void GParallelNodePrivate::confirmEvent(GGhostConfirmEvent *event)
{
    Ghost::Status sourceStatus = event->status();

    if ((Ghost::Success == sourceStatus)
            || (Ghost::Failure == sourceStatus)
            || (Ghost::Stopped == sourceStatus)) {
        if ((0 == --executeCounter) && !executeState) {
            if (terminateState) {
                setStatus(Ghost::Stopped);
            } else {
                setStatus(Ghost::Success);
            }
        }
    }
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
            postExecuteEvent(childNode);
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
