#include "grepeatuntilsuccessnode_p.h"
#include "grepeatuntilsuccessnode_p_p.h"

#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(qlcRepeatUntilSuccessNode, "GtGhost.RepeatUntilSuccessNode")

// class GRepeatUntilSuccessNode

/*!
    \qmltype RepeatUntilSuccessNode
    \instantiates GRepeatUntilSuccessNode
    \inqmlmodule GtGhost
    \inherits DecoratorNode

    fff
 */

GRepeatUntilSuccessNode::GRepeatUntilSuccessNode(QObject *parent)
    : GDecoratorNode(*new GRepeatUntilSuccessNodePrivate(), parent)
{
}

void GRepeatUntilSuccessNode::setLoopCount(int value)
{
    Q_D(GRepeatUntilSuccessNode);

    if (value < 0) {
        qCWarning(qlcRepeatUntilSuccessNode)
                << "Value is too small, reset to 0.";
        value = 0;
    }

    if (value != d->loopCount) {
        d->loopCount = value;
        emit loopCountChanged(value);
    }
}

int GRepeatUntilSuccessNode::loopCount() const
{
    Q_D(const GRepeatUntilSuccessNode);
    return d->loopCount;
}

// class GRepeatUntilSuccessNodePrivate

GRepeatUntilSuccessNodePrivate::GRepeatUntilSuccessNodePrivate()
    : GDecoratorNodePrivate(Ghost::RepeatUntilSuccessNode)
    , loopCount(0)
    , loopCounter(0)
{
}

GRepeatUntilSuccessNodePrivate::~GRepeatUntilSuccessNodePrivate()
{
}

void GRepeatUntilSuccessNodePrivate::onChildStatusChanged(GGhostSourceNode *childNode)
{
    Q_ASSERT(Ghost::Invalid != status);

    Q_CHECK_PTR(childNodes[0]);
    Q_ASSERT(childNode == childNodes[0]);

    Ghost::Status childStatus = childNode->status();

    if (Ghost::Stopped == childStatus) {
        setStatus(Ghost::Stopped);
    } else if ((Ghost::Success == childStatus)
               || (Ghost::Failure == childStatus)) {
        if (Ghost::Success == childStatus) {
            setStatus(Ghost::Success);
            return;
        }

        if ((++loopCounter >= loopCount) && (0 != loopCount)) {
            setStatus(Ghost::Failure);
            return;
        }

        GGhostNodePrivate *childptr = cast(childNodes[0]);
        if (childptr->callPrecondition()) {
            childptr->execute();
        } else {
            setStatus(breakStatus);
        }
    }
}
