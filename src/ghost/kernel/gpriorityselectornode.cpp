#include "gpriorityselectornode_p.h"
#include "gpriorityselectornode_p_p.h"

#include <QtCore/QLoggingCategory>

#include "gghostevent.h"

Q_LOGGING_CATEGORY(qlcPrioritySelectorNode, "GtGhost.PrioritySelectorNode")

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

bool GPrioritySelectorNodePrivate::initialize()
{
    sortedChildNodes = childNodes;

    resortChildNodes();

    if (GGhostNodePrivate::initialize(sortedChildNodes)) {
        setStatus(Ghost::StandBy);
        return true;
    }

    return false;
}

void GPrioritySelectorNodePrivate::reset()
{
    Q_ASSERT(Ghost::Invalid != status);
    Q_ASSERT(Ghost::StandBy != status);
    Q_ASSERT(Ghost::Running != status);

    resortChildNodes();

    QListIterator<GGhostNode *> i(sortedChildNodes);

    i.toBack();
    while (i.hasPrevious()) {
        GGhostNode *childNode = i.previous();
        if (Ghost::StandBy != cast(childNode)->status) {
            cast(childNode)->reset();
        }
    }

    setStatus(Ghost::StandBy);
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

void GPrioritySelectorNodePrivate::terminate()
{
    Q_ASSERT(Ghost::Running == status);

    GGhostNode *childNode
            = sortedChildNodes.at(executeIndex);
    cast(childNode)->terminate();
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
            setStatus(breakStatus);
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
