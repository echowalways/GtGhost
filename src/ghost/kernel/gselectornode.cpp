#include "gselectornode_p.h"
#include "gselectornode_p_p.h"

#include "gghostevent.h"

// class GSelectorNode

GSelectorNode::GSelectorNode(QObject *parent)
    : GCompositeNode(*new GSelectorNodePrivate(), parent)
{
}

// class GSelectorNodePrivate

GSelectorNodePrivate::GSelectorNodePrivate()
    : GCompositeNodePrivate(Ghost::SelectorNode)
{
}

GSelectorNodePrivate::~GSelectorNodePrivate()
{
}

void GSelectorNodePrivate::confirmEvent(GGhostConfirmEvent *event)
{
    Ghost::Status sourceStatus = event->status();

    if (Ghost::Stopped == sourceStatus) {
        setStatus(Ghost::Stopped);
    } else if (Ghost::Failure == sourceStatus) {
        executeNextChildNode();
    } else if (Ghost::Success == sourceStatus) {
        if (++unmatchCounter >= unmatchCount) {
            setStatus(Ghost::Success);
        } else {
            executeNextChildNode();
        }
    }
}

bool GSelectorNodePrivate::reset()
{
    return true;
}

void GSelectorNodePrivate::execute()
{
    Q_ASSERT(Ghost::Invalid != status);
    Q_ASSERT(Ghost::Running != status);

    setStatus(Ghost::Running);

    unmatchCounter = 0;
    executeIndex = -1;
    executeCounter = 0;

    executeNextChildNode();
}

bool GSelectorNodePrivate::terminate()
{
    return true;
}

void GSelectorNodePrivate::executeNextChildNode()
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
            setStatus(Ghost::Failure);
        } else {
            setStatus(breakStatus);
        }
    }
}
