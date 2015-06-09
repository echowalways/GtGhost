#include "gfreezenode_p.h"
#include "gfreezenode_p_p.h"

#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(qlcFreezeNode, "GtGhost.FreezeNode")

// class GFreezeNode

GFreezeNode::GFreezeNode(QObject *parent)
    : GLeafNode(*new GFreezeNodePrivate(), parent)
{
}

void GFreezeNode::setDuration(int value)
{
    Q_D(GFreezeNode);

    if (value < 1) {
        qCWarning(qlcFreezeNode)
                << "Value is too small, reset to 1.";
        value = 1;
    }

    if (value != d->duration) {
        d->duration = value;
        emit durationChanged(value);
    }
}

int GFreezeNode::duration() const
{
    Q_D(const GFreezeNode);
    return d->duration;
}

// class GFreezeNodePrivate

GFreezeNodePrivate::GFreezeNodePrivate()
    : GLeafNodePrivate(Ghost::FreezeNode)
    , duration(1)
{
}

GFreezeNodePrivate::~GFreezeNodePrivate()
{
}

void GFreezeNodePrivate::onStatusChanged(Ghost::Status status)
{
    Q_Q(GFreezeNode);

    if (Ghost::Running == status) {
        emit q->started();
    } else if (Ghost::Success == status) {
        emit q->finished();
    }
}

void GFreezeNodePrivate::reset()
{
    Q_ASSERT(Ghost::Invalid != status);
    Q_ASSERT(Ghost::StandBy != status);
    Q_ASSERT(Ghost::Running != status);

    setStatus(Ghost::StandBy);
}

void GFreezeNodePrivate::execute()
{
    Q_Q(GFreezeNode);

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

void GFreezeNodePrivate::terminate()
{
    Q_ASSERT(Ghost::Running == status);

    if (timer) {
        timer->stop();
    }

    setStatus(Ghost::Stopped);
}

void GFreezeNodePrivate::onTimeout()
{
    Q_ASSERT(Ghost::Running == status);

    setStatus(Ghost::Success);
}

// moc_gfreezenode_p.cpp
#include "moc_gfreezenode_p.cpp"
