#include "grandomselectornode_p.h"
#include "grandomselectornode_p_p.h"

#include <QtCore/QLoggingCategory>

#include "gghostevents.h"

Q_LOGGING_CATEGORY(qlcRandomSelectorNode, "GtGhost.RandomSelectorNode")

// class GRandomSelectorNode

/*!
    \qmltype RandomSelectorNode
    \instantiates GRandomSelectorNode
    \inqmlmodule GtGhost
    \inherits CompositeNode

    fff
 */

GRandomSelectorNode::GRandomSelectorNode(QObject *parent)
    : GCompositeNode(*new GRandomSelectorNodePrivate(), parent)
{
}

void GRandomSelectorNode::setUpdateMode(Ghost::UpdateMode value)
{
    Q_D(GRandomSelectorNode);

    if (value != d->updateMode) {
        d->updateMode = value;
        emit updateModeChanged(value);
    }
}

void GRandomSelectorNode::setRandomMode(Ghost::RandomMode value)
{
    Q_D(GRandomSelectorNode);

    if (value != d->randomMode) {
        d->randomMode = value;
        emit randomModeChanged(value);
    }
}

Ghost::UpdateMode GRandomSelectorNode::updateMode() const
{
    Q_D(const GRandomSelectorNode);
    return d->updateMode;
}

Ghost::RandomMode GRandomSelectorNode::randomMode() const
{
    Q_D(const GRandomSelectorNode);
    return d->randomMode;
}

void GRandomSelectorNode::componentComplete()
{
    Q_D(GRandomSelectorNode);

    GCompositeNode::componentComplete();

    if (Ghost::StandBy == d->status) {
        d->resortChildNodes();
    }
}

// class GRandomSelectorNodePrivate

GRandomSelectorNodePrivate::GRandomSelectorNodePrivate()
    : GCompositeNodePrivate(Ghost::RandomSelectorNode)
    , updateMode(Ghost::ResetOnly)
    , randomMode(Ghost::Parity)
{
}

GRandomSelectorNodePrivate::~GRandomSelectorNodePrivate()
{
}

void GRandomSelectorNodePrivate::confirmEvent(GGhostConfirmEvent *event)
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

bool GRandomSelectorNodePrivate::reset()
{
    resortChildNodes();

    return true;
}

void GRandomSelectorNodePrivate::execute()
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

bool GRandomSelectorNodePrivate::terminate()
{
    return true;
}

void GRandomSelectorNodePrivate::executeNextChildNode()
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

void GRandomSelectorNodePrivate::resortChildNodes()
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
