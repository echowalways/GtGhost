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

void GAlwaysFailureItemPrivate::onChildStatusChanged(GGhostItem *child, Ghost::Status status)
{
    Q_UNUSED(child);

    if (Ghost::Invalid == this->status) {
        return;
    }

    Q_CHECK_PTR(childItems[0]);
    Q_ASSERT(child == childItems[0]);

    if (Ghost::Stopped == status) {
        setStatus(Ghost::Stopped);
    } else if ((Ghost::Success == status)
               || (Ghost::Failure == status)) {
        setStatus(Ghost::Failure);
    } else {
        Q_UNREACHABLE();
    }
}

void GAlwaysFailureItemPrivate::executeChildItem()
{
    setFailureIfPreconditionFalse();
}
