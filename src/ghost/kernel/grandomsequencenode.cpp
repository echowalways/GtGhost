#include "grandomsequencenode_p.h"
#include "grandomsequencenode_p_p.h"

#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(qlcRandomSequenceNode, "GtGhost.RandomSequenceNode")

// class GRandomSequenceNode

/*!
    \qmltype RandomSequenceNode
    \instantiates GRandomSequenceNode
    \inqmlmodule GtGhost
    \inherits CompositeNode

    fff
 */

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

void GRandomSequenceNodePrivate::onChildStatusChanged(GGhostSourceNode *childNode)
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

bool GRandomSequenceNodePrivate::initialize()
{
    sortedChildNodes = childNodes;

    resortChildNodes();

    if (GGhostNodePrivate::initialize(sortedChildNodes)) {
        setStatus(Ghost::StandBy);
        return true;
    }

    return false;
}

void GRandomSequenceNodePrivate::reset()
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

void GRandomSequenceNodePrivate::terminate()
{
    Q_ASSERT(Ghost::Running == status);

    GGhostNode *childNode
            = sortedChildNodes.at(executeIndex);
    cast(childNode)->terminate();
}

void GRandomSequenceNodePrivate::executeNextChildNode()
{
    bool r = true;

    while (++executeIndex < sortedChildNodes.count()) {
        GGhostNode *childNode = sortedChildNodes.at(executeIndex);
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
