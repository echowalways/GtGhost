#include "grandomsequencenode_p.h"
#include "grandomsequencenode_p_p.h"

#include <QtCore/QLoggingCategory>

#include "gghostevents.h"

Q_LOGGING_CATEGORY(qlcRandomSequenceNode, "GtGhost.RandomSequenceNode")

// class GRandomSequenceNode

GRandomSequenceNode::GRandomSequenceNode(QObject *parent)
    : GCompositeNode(*new GRandomSequenceNodePrivate(), parent)
{
}

void GRandomSequenceNode::setUpdateMode(Ghost::UpdateMode value)
{
    Q_D(GRandomSequenceNode);

    if (value != d->updateMode) {
        d->updateMode = value;
        emit updateModeChanged(value);
    }
}

void GRandomSequenceNode::setRandomMode(Ghost::RandomMode value)
{
    Q_D(GRandomSequenceNode);

    if (value != d->randomMode) {
        d->randomMode = value;
        emit randomModeChanged(value);
    }
}

Ghost::UpdateMode GRandomSequenceNode::updateMode() const
{
    Q_D(const GRandomSequenceNode);
    return d->updateMode;
}

Ghost::RandomMode GRandomSequenceNode::randomMode() const
{
    Q_D(const GRandomSequenceNode);
    return d->randomMode;
}

void GRandomSequenceNode::componentComplete()
{
    Q_D(GRandomSequenceNode);

    GCompositeNode::componentComplete();

    if (Ghost::StandBy == d->status) {
        d->resortChildNodes();
    }
}

// class GRandomSequenceNodePrivate

GRandomSequenceNodePrivate::GRandomSequenceNodePrivate()
    : GCompositeNodePrivate(Ghost::RandomSequenceNode)
    , updateMode(Ghost::ResetOnly)
    , randomMode(Ghost::Parity)
{
}

GRandomSequenceNodePrivate::~GRandomSequenceNodePrivate()
{
}

void GRandomSequenceNodePrivate::confirmEvent(GGhostConfirmEvent *event)
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

bool GRandomSequenceNodePrivate::reset()
{
    resortChildNodes();

    return true;
}

void GRandomSequenceNodePrivate::execute()
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

bool GRandomSequenceNodePrivate::terminate()
{
    return true;
}

void GRandomSequenceNodePrivate::executeNextChildNode()
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
            setStatus(brokenStatus);
        }
    }
}

void GRandomSequenceNodePrivate::resortChildNodes()
{
    if (Ghost::Parity == randomMode) {
        Q_FOREACH (GGhostNode *childNode, childNodes) {
            cast(childNode)->sortIndex = qrand();
        }
    } else {
        Q_FOREACH (GGhostNode *childNode, childNodes) {
            cast(childNode)->sortIndex
                    = qrand() % cast(childNode)->callWeight();
        }
    }

    sort(sortedChildNodes);
}
