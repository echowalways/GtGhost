#include "galwaysfailureitem.h"
#include "galwaysfailureitem_p.h"

#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(qlcAlwaysFailureItem, "GtGhost.AlwaysFailureItem")

// class GAlwaysFailureItem

GAlwaysFailureItem::GAlwaysFailureItem(QObject *parent)
    : GDecoratorItem(*new GAlwaysFailureItemPrivate(), parent)
{
}

// class GAlwaysFailureItemPrivate

GAlwaysFailureItemPrivate::GAlwaysFailureItemPrivate()
{
}

GAlwaysFailureItemPrivate::~GAlwaysFailureItemPrivate()
{
}

void GAlwaysFailureItemPrivate::onChildStatusChanged(GGhostItem *child)
{
    if (Ghost::Invalid == status) {
        return;
    }

    Q_CHECK_PTR(childItems[0]);
    Q_ASSERT(child == childItems[0]);

    Ghost::Status childStatus = child->status();

    if (Ghost::Stopped == childStatus) {
        setStatus(Ghost::Stopped);
    } else if ((Ghost::Success == childStatus)
               || (Ghost::Failure == childStatus)) {
        setStatus(Ghost::Failure);
    } else {
        Q_UNREACHABLE();
    }
}

void GAlwaysFailureItemPrivate::executeChildItem()
{
    setFailureIfPreconditionFalse();
}
