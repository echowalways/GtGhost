#include "gselectornode_p.h"
#include "gselectornode_p_p.h"

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

void GSelectorNodePrivate::onChildStatusChanged(GGhostSourceNode *childNode)
{
    Q_ASSERT(Ghost::Invalid != status);

    Ghost::Status childStatus = childNode->status();

    if (Ghost::Stopped == childStatus) {
        setStatus(Ghost::Stopped);
    } else if (Ghost::Failure == childStatus) {
        executeNextChildNode();
    } else if (Ghost::Success == childStatus) {
        if (++unmatchCounter >= unmatchCount) {
            setStatus(Ghost::Success);
        } else {
            executeNextChildNode();
        }
    }
}

void GSelectorNodePrivate::reset()
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

void GSelectorNodePrivate::terminate()
{
    Q_ASSERT(Ghost::Running == status);

    GGhostNode *childNode
            = childNodes.at(executeIndex);
    cast(childNode)->terminate();
}

void GSelectorNodePrivate::executeNextChildNode()
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
            setStatus(Ghost::Failure);
        } else {
            setStatus(breakStatus);
        }
    }
}
