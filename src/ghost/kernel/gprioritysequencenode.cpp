#include "gprioritysequencenode_p.h"
#include "gprioritysequencenode_p_p.h"

#include <QtCore/QLoggingCategory>

#include "gghostevent.h"

Q_LOGGING_CATEGORY(qlcPrioritySequenceNode, "GtGhost.PrioritySequenceNode")

// class GPrioritySequenceNode

/*!
    \qmltype PrioritySequenceNode
    \instantiates GPrioritySequenceNode
    \inqmlmodule GtGhost
    \inherits CompositeNode

    fff
 */

GPrioritySequenceNode::GPrioritySequenceNode(QObject *parent)
    : GCompositeNode(*new GPrioritySequenceNodePrivate(), parent)
{
}

void GPrioritySequenceNode::setUpdateMode(Ghost::UpdateMode value)
{
    Q_D(GPrioritySequenceNode);

    if (value != d->updateMode) {
        d->updateMode = value;
        emit updateModeChanged(value);
    }
}

Ghost::UpdateMode GPrioritySequenceNode::updateMode() const
{
    Q_D(const GPrioritySequenceNode);
    return d->updateMode;
}

// class GPrioritySequenceNodePrivate

GPrioritySequenceNodePrivate::GPrioritySequenceNodePrivate()
    : GCompositeNodePrivate(Ghost::PrioritySequenceNode)
    , updateMode(Ghost::ResetOnly)
{
}

GPrioritySequenceNodePrivate::~GPrioritySequenceNodePrivate()
{
}

void GPrioritySequenceNodePrivate::confirmEvent(GGhostConfirmEvent *event)
{
    Ghost::Status sourceStatus = event->status();

    if (Ghost::Stopped == sourceStatus) {
        setStatus(Ghost::Stopped);
    } else if (Ghost::Success == sourceStatus) {
        executeNextChildNode();
    } else if (Ghost::Failure == sourceStatus) {
        if (++unmatchCounter >= unmatchCount) {
            setStatus(Ghost::Failure);
        } else {
            executeNextChildNode();
        }
    }
}

bool GPrioritySequenceNodePrivate::initialize()
{
    sortedChildNodes = childNodes;

    resortChildNodes();

    if (GGhostNodePrivate::initialize(sortedChildNodes)) {
        setStatus(Ghost::StandBy);
        return true;
    }

    return false;
}

void GPrioritySequenceNodePrivate::reset()
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

void GPrioritySequenceNodePrivate::execute()
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

void GPrioritySequenceNodePrivate::terminate()
{
    Q_ASSERT(Ghost::Running == status);

    GGhostNode *childNode
            = sortedChildNodes.at(executeIndex);
    cast(childNode)->terminate();
}

void GPrioritySequenceNodePrivate::executeNextChildNode()
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
            setStatus(Ghost::Success);
        } else {
            setStatus(breakStatus);
        }
    }
}

void GPrioritySequenceNodePrivate::resortChildNodes()
{
    Q_FOREACH (GGhostNode *childNode, childNodes) {
        cast(childNode)->sortIndex = cast(childNode)->callWeight();
    }

    sort(sortedChildNodes);
}
