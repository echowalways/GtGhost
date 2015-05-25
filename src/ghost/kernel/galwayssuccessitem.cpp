#include "galwayssuccessitem.h"
#include "galwayssuccessitem_p.h"

#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(qlcAlwaysSuccessItem, "GtGhost.AlwaysSuccessItem")

// class GAlwaysSuccessItem

GAlwaysSuccessItem::GAlwaysSuccessItem(QObject *parent)
    : GDecoratorItem(*new GAlwaysSuccessItemPrivate(), parent)
{
}

// class GAlwaysSuccessItemPrivate

GAlwaysSuccessItemPrivate::GAlwaysSuccessItemPrivate()
{
}

GAlwaysSuccessItemPrivate::~GAlwaysSuccessItemPrivate()
{
}

void GAlwaysSuccessItemPrivate::onChildStatusChanged(GGhostItem *child, Ghost::Status status)
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
        setStatus(Ghost::Success);
    } else {
        Q_UNREACHABLE();
    }
}

void GAlwaysSuccessItemPrivate::executeChildItem()
{
    setSuccessIfPreconditionFalse();
}
