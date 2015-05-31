#include "gcooldownnode_p.h"
#include "gcooldownnode_p_p.h"

#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(qlcCooldownNode, "GtGhost.CooldownNode")

// class GCooldownNode

GCooldownNode::GCooldownNode(QObject *parent)
    : GLeafNode(*new GCooldownNodePrivate(), parent)
{
}

void GCooldownNode::setDuration(int value)
{
    Q_D(GCooldownNode);

    if (value < 1) {
        qCWarning(qlcCooldownNode)
                << "Value is too small, reset to 1.";
        value = 1;
    }

    if (value != d->duration) {
        d->duration = value;
        emit durationChanged(value);
    }
}

int GCooldownNode::duration() const
{
    Q_D(const GCooldownNode);
    return d->duration;
}

// class GCooldownNodePrivate

GCooldownNodePrivate::GCooldownNodePrivate()
    : GLeafNodePrivate(Ghost::CooldownNode)
    , duration(1)
{
}

GCooldownNodePrivate::~GCooldownNodePrivate()
{
}

void GCooldownNodePrivate::onStatusChanged(Ghost::Status status)
{
    Q_Q(GCooldownNode);

    if (Ghost::Running == status) {
        emit q->started();
    } else if (Ghost::Success == status) {
        emit q->finished();
    }
}

void GCooldownNodePrivate::reset()
{
    Q_ASSERT(Ghost::Invalid != status);
    Q_ASSERT(Ghost::StandBy != status);
    Q_ASSERT(Ghost::Running != status);

    setStatus(Ghost::StandBy);
}

void GCooldownNodePrivate::execute()
{
    Q_Q(GCooldownNode);

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

void GCooldownNodePrivate::terminate()
{
    Q_ASSERT(Ghost::Running == status);

    if (timer) {
        timer->stop();
    }

    setStatus(Ghost::Stopped);
}

void GCooldownNodePrivate::onTimeout()
{
    Q_ASSERT(Ghost::Running == status);

    setStatus(Ghost::Success);
}

// moc_gcooldownnode_p.cpp
#include "moc_gcooldownnode_p.cpp"
