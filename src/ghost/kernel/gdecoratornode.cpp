#include "gdecoratornode_p.h"
#include "gdecoratornode_p_p.h"

// class GDecoratorNode

GDecoratorNode::GDecoratorNode(GDecoratorNodePrivate &dd, QObject *parent)
    : GGhostNode(dd, parent)
{
}

void GDecoratorNode::setBrokenStatus(Ghost::Status value)
{
    Q_D(GDecoratorNode);

    if ((Ghost::Success != value)
            && (Ghost::Failure != value)) {
        qWarning("GtGhost : Invalid broken status: '%s'",
                 Ghost::toString(value));
        return;
    }

    if (value != d->brokenStatus) {
        d->brokenStatus = value;
        emit brokenStatusChanged(value);
    }
}

Ghost::Status GDecoratorNode::brokenStatus() const
{
    Q_D(const GDecoratorNode);
    return d->brokenStatus;
}

// class GDecoratorNodePrivate

GDecoratorNodePrivate::GDecoratorNodePrivate(Ghost::NodeType nodeType)
    : GGhostNodePrivate(Ghost::DecoratorNode, nodeType)
    , brokenStatus(Ghost::Failure)
{
}

GDecoratorNodePrivate::~GDecoratorNodePrivate()
{
}

bool GDecoratorNodePrivate::reset()
{
    return true;
}

void GDecoratorNodePrivate::execute()
{
    Q_CHECK_PTR(childNodes[0]);
    Q_ASSERT(Ghost::Invalid != status);
    Q_ASSERT(Ghost::Running != status);

    setStatus(Ghost::Running);

    GGhostNodePrivate *childptr = cast(childNodes[0]);
    if (childptr->callPrecondition()) {
        postExecuteEvent(childNodes[0]);
    } else {
        setStatus(brokenStatus);
    }
}

bool GDecoratorNodePrivate::terminate()
{
    return true;
}
