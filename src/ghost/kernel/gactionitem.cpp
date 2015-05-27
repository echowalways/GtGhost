#include "gactionitem.h"
#include "gactionitem_p.h"

#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(qlcActionItem, "GtGhost.ActionNode")

// class GActionItem

GActionItem::GActionItem(QObject *parent)
    : GGhostItem(*new GActionItemPrivate(), parent)
{
}

Ghost::NodeType GActionItem::nodeType() const
{
    return Ghost::ActionNode;
}

Ghost::ItemType GActionItem::itemType() const
{
    return Ghost::ActionItem;
}

void GActionItem::setSuccessStatus()
{
    d_func()->setStatus(Ghost::Success);
}

void GActionItem::setFailureStatus()
{
    d_func()->setStatus(Ghost::Failure);
}

void GActionItem::setStoppedStatus()
{
    d_func()->setStatus(Ghost::Stopped);
}

// class GActionItemPrivate

GActionItemPrivate::GActionItemPrivate()
{
}

GActionItemPrivate::~GActionItemPrivate()
{
}

bool GActionItemPrivate::initialize()
{
    if (!childItems.isEmpty()) {
        qCWarning(qlcActionItem)
                << "Does not allow child items.";
        return false;
    }

    setStatus(Ghost::StandBy);

    return true;
}

void GActionItemPrivate::reset()
{
    Q_ASSERT(Ghost::Invalid != status);
    Q_ASSERT(Ghost::StandBy != status);
    Q_ASSERT(Ghost::Running != status);

    emit q_func()->reset();

    setStatus(Ghost::StandBy);
}

void GActionItemPrivate::execute()
{
    Q_ASSERT(Ghost::Invalid != status);
    Q_ASSERT(Ghost::Running != status);

    setStatus(Ghost::Running);

    emit q_func()->execute();
}

void GActionItemPrivate::terminate()
{
    Q_ASSERT(Ghost::Running == status);

    emit q_func()->terminate();
}
