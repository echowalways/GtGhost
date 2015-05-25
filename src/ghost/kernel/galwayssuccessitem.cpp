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

void GAlwaysSuccessItemPrivate::onChildStatusChanged(GGhostItem *child)
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
        setStatus(Ghost::Success);
    } else {
        Q_UNREACHABLE();
    }
}

void GAlwaysSuccessItemPrivate::executeChildItem()
{
    setSuccessIfPreconditionFalse();
}
