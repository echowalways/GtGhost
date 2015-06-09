#include "gactionnode_p.h"
#include "gactionnode_p_p.h"

#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(qlcActionNode, "GtGhost.ActionNode")

// class GActionNode

GActionNode::GActionNode(QObject *parent)
    : GLeafNode(*new GActionNodePrivate(), parent)
{
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

void GActionNode::setTimeout(int value)
{
    Q_D(GActionNode);

    if (value < 0) {
        qCWarning(qlcActionNode)
                << "Value is too small, reset to 0.";
        value = 0;
    }

    if (value != d->timeout) {
        d->timeout = value;
        emit timeoutChanged(value);
    }
}

int GActionNode::timeout() const
{
    Q_D(const GActionNode);
    return d->timeout;
}

// class GActionNodePrivate

GActionNodePrivate::GActionNodePrivate()
    : GLeafNodePrivate(Ghost::ActionNode)
    , timeout(0)
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

    if (timeout > 0) {
        if (!timer) {
            timer = new QTimer(q);
            timer->setSingleShot(true);

            QObject::connect(timer.data(), &QTimer::timeout,
                             q, &GActionNode::setFailureStatus);
        }

        timer->setInterval(timeout);
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
}
