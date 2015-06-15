#include "gactionnode_p.h"
#include "gactionnode_p_p.h"

#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(qlcActionNode, "GtGhost.ActionNode")

// class GActionNode

/*!
    \qmltype ActionNode
    \instantiates GActionNode
    \inqmlmodule GtGhost
    \inherits LeafNode

    fff
 */

GActionNode::GActionNode(QObject *parent)
    : GLeafNode(*new GActionNodePrivate(), parent)
{
}

void GActionNode::setDuration(int value)
{
    Q_D(GActionNode);

    if (value < 0) {
        qCWarning(qlcActionNode)
                << "Value is too small, reset to 0.";
        value = 0;
    }

    if (value != d->duration) {
        d->duration = value;
        emit durationChanged(value);
    }
}

int GActionNode::duration() const
{
    Q_D(const GActionNode);
    return d->duration;
}

void GActionNode::setSuccessStatus()
{
    Q_D(GActionNode);

    if (d->timer) {
        d->timer->stop();
    }

    d->setStatus(Ghost::Success);
}

void GActionNode::setFailureStatus()
{
    Q_D(GActionNode);

    if (d->timer) {
        d->timer->stop();
    }

    d->setStatus(Ghost::Failure);
}

void GActionNode::setStoppedStatus()
{
    Q_D(GActionNode);

    if (d->timer) {
        d->timer->stop();
    }

    d->setStatus(Ghost::Stopped);
}

// class GActionNodePrivate

GActionNodePrivate::GActionNodePrivate()
    : GLeafNodePrivate(Ghost::ActionNode)
    , duration(0)
{
}

GActionNodePrivate::~GActionNodePrivate()
{
}

void GActionNodePrivate::reset()
{
    Q_Q(GActionNode);

    Q_ASSERT(Ghost::Invalid != status);
    Q_ASSERT(Ghost::StandBy != status);
    Q_ASSERT(Ghost::Running != status);

    emit q->reset();

    setStatus(Ghost::StandBy);
}

void GActionNodePrivate::execute()
{
    Q_Q(GActionNode);

    Q_ASSERT(Ghost::Invalid != status);
    Q_ASSERT(Ghost::Running != status);

    setStatus(Ghost::Running);

    if (duration > 0) {
        if (!timer) {
            timer = new QTimer(q);
            timer->setSingleShot(true);

            QObject::connect(timer.data(), &QTimer::timeout,
                             q, &GActionNode::setFailureStatus);
        }

        timer->setInterval(duration);
        timer->start();
    }

    emit q->execute();
}

void GActionNodePrivate::terminate()
{
    Q_Q(GActionNode);

    Q_ASSERT(Ghost::Running == status);

    if (timer) {
        timer->stop();
    }

    emit q->terminate();

    setStatus(Ghost::Stopped);
}
