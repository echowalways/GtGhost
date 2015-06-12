#include "gdecoratornode_p.h"
#include "gdecoratornode_p_p.h"

#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(qlcDecoratorNode, "GtGhost.DecoratorNode")

// class GDecoratorNode

GDecoratorNode::GDecoratorNode(GDecoratorNodePrivate &dd, QObject *parent)
    : GGhostNode(dd, parent)
{
}

void GDecoratorNode::setBreakStatus(Ghost::Status value)
{
    Q_D(GDecoratorNode);

    if ((Ghost::Invalid == value)
            || (Ghost::Running == value)
            || (Ghost::Stopped == value)) {
        qCWarning(qlcDecoratorNode)
                << "Invalid break status: " << Ghost::toString(value);
        return;
    }

    if (value != d->breakStatus) {
        d->breakStatus = value;
        emit breakStatusChanged(value);
    }
}

Ghost::Status GDecoratorNode::breakStatus() const
{
    Q_D(const GDecoratorNode);
    return d->breakStatus;
}

// class GDecoratorNodePrivate

GDecoratorNodePrivate::GDecoratorNodePrivate(Ghost::NodeType nodeType)
    : GGhostNodePrivate(Ghost::DecoratorNode, nodeType)
    , breakStatus(Ghost::Failure)
{
}

GDecoratorNodePrivate::~GDecoratorNodePrivate()
{
}

void GDecoratorNodePrivate::reset()
{
    Q_CHECK_PTR(childNodes[0]);
    Q_ASSERT(Ghost::Invalid != status);
    Q_ASSERT(Ghost::StandBy != status);
    Q_ASSERT(Ghost::Running != status);

    cast(childNodes[0])->reset();

    setStatus(Ghost::StandBy);
}

void GDecoratorNodePrivate::execute()
{
    Q_CHECK_PTR(childNodes[0]);
    Q_ASSERT(Ghost::Invalid != status);
    Q_ASSERT(Ghost::Running != status);

    setStatus(Ghost::Running);

    GGhostNodePrivate *childptr = cast(childNodes[0]);
    if (childptr->callPrecondition()) {
        childptr->execute();
    } else {
        setStatus(breakStatus);
    }
}

void GDecoratorNodePrivate::terminate()
{
    Q_CHECK_PTR(childNodes[0]);
    Q_ASSERT(Ghost::Running == status);

    cast(childNodes[0])->terminate();
}
