#include "gcompositenode_p.h"
#include "gcompositenode_p_p.h"

#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(qlcCompositeNode, "GtGhost.CompositeNode")

// class GCompositeNode

GCompositeNode::GCompositeNode(GCompositeNodePrivate &dd, QObject *parent)
    : GGhostNode(dd, parent)
{
}

void GCompositeNode::setBreakStatus(Ghost::Status value)
{
    Q_D(GCompositeNode);

    if ((Ghost::Invalid == value)
            || (Ghost::StandBy == value)
            || (Ghost::Running == value)) {
        qCWarning(qlcCompositeNode)
                << "Invalid break status: " << Ghost::toString(value);
        return;
    }

    if (value != d->breakStatus) {
        d->breakStatus = value;
        emit breakStatusChanged(value);
    }
}

void GCompositeNode::setUnmatchCount(int value)
{
    Q_D(GCompositeNode);

    if (value < 1) {
        qCWarning(qlcCompositeNode)
                << "Value is too small, reset to 1.";
        value = 1;
    }

    if (value != d->unmatchCount) {
        d->unmatchCount = value;
        emit unmatchCountChanged(value);
    }
}

Ghost::Status GCompositeNode::breakStatus() const
{
    Q_D(const GCompositeNode);
    return d->breakStatus;
}

int GCompositeNode::unmatchCount() const
{
    Q_D(const GCompositeNode);
    return d->unmatchCount;
}

// class GCompositeNodePrivate

GCompositeNodePrivate::GCompositeNodePrivate(Ghost::NodeType nodeType)
    : GGhostNodePrivate(Ghost::CompositeNode, nodeType)
    , breakStatus(Ghost::Failure)
    , unmatchCount(1)
    , unmatchCounter(-1)
    , executeIndex(0)
    , executeCounter(-1)
{
}

GCompositeNodePrivate::~GCompositeNodePrivate()
{
}
