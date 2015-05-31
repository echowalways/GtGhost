#include "gtimeoutnode_p.h"
#include "gtimeoutnode_p_p.h"

#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(qlcTimeoutNode, "GtGhost.TimeoutNode")

// class GTimeoutNode

GTimeoutNode::GTimeoutNode(QObject *parent)
    : GLeafNode(*new GTimeoutNodePrivate(), parent)
{
}

void GTimeoutNode::setDuration(int value)
{
    Q_D(GTimeoutNode);

    if (value < 1) {
        qCWarning(qlcTimeoutNode)
                << "Value is too small, reset to 1.";
        value = 1;
    }

    if (value != d->duration) {
        d->duration = value;
        emit durationChanged(value);
    }
}

int GTimeoutNode::duration() const
{
    Q_D(const GTimeoutNode);
    return d->duration;
}

void GTimeoutNode::finish()
{
    Q_D(GTimeoutNode);

    if (Ghost::Running == d->status) {
        if (d->timer) {
            d->timer->stop();
        }
        d->setStatus(Ghost::Success);
    }
}

// class GTimeoutNodePrivate

GTimeoutNodePrivate::GTimeoutNodePrivate()
    : GLeafNodePrivate(Ghost::TimeoutNode)
{
}

GTimeoutNodePrivate::~GTimeoutNodePrivate()
{
}

void GTimeoutNodePrivate::onStatusChanged(Ghost::Status status)
{
    Q_Q(GTimeoutNode);

    if (Ghost::Running == status) {
        emit q->started();
    } else if (Ghost::Success == status) {
        emit q->finished();
    } else if (Ghost::Failure == status) {
        emit q->timeout();
    }
}

void GTimeoutNodePrivate::reset()
{
    Q_ASSERT(Ghost::Invalid != status);
    Q_ASSERT(Ghost::StandBy != status);
    Q_ASSERT(Ghost::Running != status);

    setStatus(Ghost::StandBy);
}

void GTimeoutNodePrivate::execute()
{
    Q_Q(GTimeoutNode);

    Q_ASSERT(Ghost::Invalid != status);
    Q_ASSERT(Ghost::Running != status);

    if (!timer) {
        timer = new QTimer(q);
        timer->setSingleShot(true);

        QObject::connect(timer.data(), SIGNAL(timeout()),
                         q, SLOT(onTimeout()));
    }

    timer->setInterval(duration);
    timer->start();

    setStatus(Ghost::Running);
}

void GTimeoutNodePrivate::terminate()
{
    Q_ASSERT(Ghost::Running == status);

    if (timer) {
        timer->stop();
    }

    setStatus(Ghost::Stopped);
}

void GTimeoutNodePrivate::onTimeout()
{
    Q_ASSERT(Ghost::Running == status);

    setStatus(Ghost::Failure);
}

// moc_gtimeoutnode_p.cpp
#include "moc_gtimeoutnode_p.cpp"
