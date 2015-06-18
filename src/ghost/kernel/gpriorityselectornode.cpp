#include "gpriorityselectornode_p.h"
#include "gpriorityselectornode_p_p.h"

#include "gghostevents.h"

// class GPrioritySelectorNode

GPrioritySelectorNode::GPrioritySelectorNode(QObject *parent)
    : GCompositeNode(*new GPrioritySelectorNodePrivate(), parent)
{
}

void GPrioritySelectorNode::setUpdateMode(Ghost::UpdateMode value)
{
    Q_D(GPrioritySelectorNode);

    if (value != d->updateMode) {
        d->updateMode = value;
        emit updateModeChanged(value);
    }
}

Ghost::UpdateMode GPrioritySelectorNode::updateMode() const
{
    Q_D(const GPrioritySelectorNode);
    return d->updateMode;
}

void GPrioritySelectorNode::componentComplete()
{
    Q_D(GPrioritySelectorNode);

    GCompositeNode::componentComplete();

    if (Ghost::StandBy == d->status) {
        d->resortChildNodes();
    }
}

// class GPrioritySelectorNodePrivate

GPrioritySelectorNodePrivate::GPrioritySelectorNodePrivate()
    : GCompositeNodePrivate(Ghost::PrioritySelectorNode)
    , updateMode(Ghost::ResetOnly)
{
}

GPrioritySelectorNodePrivate::~GPrioritySelectorNodePrivate()
{
}

void GPrioritySelectorNodePrivate::confirmEvent(GGhostConfirmEvent *event)
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

bool GPrioritySelectorNodePrivate::reset()
{
    resortChildNodes();

    return true;
}

void GPrioritySelectorNodePrivate::execute()
{
    Q_ASSERT(Ghost::Invalid != status);
    Q_ASSERT(Ghost::Running != status);

    setStatus(Ghost::Running);

    if (Ghost::Everytime == updateMode) {
        resortChildNodes();
    }

    unmatchCounter = 0;
    executeIndex = -1;
    executeCounter = 0;

    executeNextChildNode();
}

bool GPrioritySelectorNodePrivate::terminate()
{
    return true;
}

void GPrioritySelectorNodePrivate::executeNextChildNode()
{
    bool r = true;

    while (++executeIndex < sortedChildNodes.count()) {
        GGhostNode *childNode = sortedChildNodes.at(executeIndex);
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
            setStatus(brokenStatus);
        }
    }
}

void GPrioritySelectorNodePrivate::resortChildNodes()
{
    Q_FOREACH (GGhostNode *childNode, childNodes) {
        cast(childNode)->sortIndex = cast(childNode)->callWeight();
    }

    sort(sortedChildNodes);
}
