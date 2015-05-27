#include "gidleactionitem.h"
#include "gidleactionitem_p.h"

#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(qlcIdleActionItem, "GtGhost.IdleActionNode")

// class GIdleActionItem

GIdleActionItem::GIdleActionItem(QObject *parent)
    : GGhostItem(*new GIdleActionItemPrivate(), parent)
{
}

Ghost::NodeType GIdleActionItem::nodeType() const
{
    return Ghost::ActionNode;
}

Ghost::ItemType GIdleActionItem::itemType() const
{
    return Ghost::IdleActionItem;
}

void GIdleActionItem::setDuration(int value)
{
    Q_D(GIdleActionItem);

    if (value != d->duration) {
        d->duration = value;
        emit durationChanged(value);
    }
}

int GIdleActionItem::duration() const
{
    Q_D(const GIdleActionItem);
    return d->duration;
}

// class GIdleActionItemPrivate

GIdleActionItemPrivate::GIdleActionItemPrivate()
    : duration(0)
{
}

GIdleActionItemPrivate::~GIdleActionItemPrivate()
{
}

bool GIdleActionItemPrivate::initialize()
{
    if (!childItems.isEmpty()) {
        qCWarning(qlcIdleActionItem)
                << "Does not allow child items.";
        return false;
    }

    setStatus(Ghost::StandBy);

    return true;
}

void GIdleActionItemPrivate::reset()
{
    Q_ASSERT(Ghost::Invalid != status);
    Q_ASSERT(Ghost::StandBy != status);
    Q_ASSERT(Ghost::Running != status);

    setStatus(Ghost::StandBy);
}

void GIdleActionItemPrivate::execute()
{
    Q_Q(GIdleActionItem);

    Q_ASSERT(Ghost::Invalid != status);
    Q_ASSERT(Ghost::Running != status);

    setStatus(Ghost::Running);

    if (duration <= 0) {
        setStatus(Ghost::Failure);
    } else {
        if (!timer) {
            timer = new QTimer(q);
            timer->setSingleShot(true);

            QObject::connect(timer.data(), SIGNAL(timeout()),
                             q, SLOT(onTimeout()));
        }

        timer->setInterval(duration);
        timer->start();
    }
}

void GIdleActionItemPrivate::terminate()
{
    Q_ASSERT(Ghost::Running == status);

    if (timer) {
        timer->stop();
    }

    setStatus(Ghost::Stopped);
}

void GIdleActionItemPrivate::onTimeout()
{
    Q_ASSERT(Ghost::Running == status);

    setStatus(Ghost::Success);
}

// moc_gidleactionitem.cpp
#include "moc_gidleactionitem.cpp"
