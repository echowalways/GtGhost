#include "gactionnode_p.h"
#include "gactionnode_p_p.h"

// class GActionNode

GActionNode::GActionNode(QObject *parent)
    : GLeafNode(*new GActionNodePrivate(), parent)
{
}

void GActionNode::setDuration(int value)
{
    Q_D(GActionNode);

    if (value < 0) {
        qWarning("GtGhost : Value is too small, reset to 0.");
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

void GActionNode::setSuccess()
{
    Q_D(GActionNode);

    if (d->timer) {
        d->timer->stop();
    }

    d->setStatus(Ghost::Success);
}

void GActionNode::setFailure()
{
    Q_D(GActionNode);

    if (d->timer) {
        d->timer->stop();
    }

    d->setStatus(Ghost::Failure);
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

bool GActionNodePrivate::reset()
{
    emit q_func()->reset();

    return true;
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
                             q, &GActionNode::setFailure);
        }

        timer->setInterval(duration);
        timer->start();
    }

    emit q->execute();
}

bool GActionNodePrivate::terminate()
{
    if (timer) {
        timer->stop();
    }

    emit q_func()->terminate();

    return true;
}
