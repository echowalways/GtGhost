#include "gdecoratoritem.h"
#include "gdecoratoritem_p.h"

#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(qlcDecoratorItem, "GtGhost.DecoratorItem")

// class GDecoratorItem

GDecoratorItem::GDecoratorItem(GDecoratorItemPrivate &dd, QObject *parent)
    : GGhostItem(dd, parent)
{
}

// class GDecoratorItemPrivate

GDecoratorItemPrivate::GDecoratorItemPrivate()
{
}

GDecoratorItemPrivate::~GDecoratorItemPrivate()
{
}

bool GDecoratorItemPrivate::initialize()
{
    if (childItems.count() != 1) {
        qDebug(qlcDecoratorItem)
                << "Allows only one child node.";
        return false;
    }

    bool hasError = false;
    Q_FOREACH (GGhostItem *childItem, childItems) {
        GGhostItemPrivate *childptr
                = GGhostItemPrivate::dptr(childItem);
        if (!childptr->initialize()) {
            hasError = true;
        }
    }
    if (hasError) {
        return hasError;
    }

    setStatus(Ghost::StandBy);

    return true;
}

void GDecoratorItemPrivate::reset()
{
    Q_CHECK_PTR(childItems[0]);
    Q_ASSERT(Ghost::Invalid != status);
    Q_ASSERT(Ghost::StandBy != status);
    Q_ASSERT(Ghost::Running != status);

    dptr(childItems[0])->reset();
    setStatus(Ghost::StandBy);
}

void GDecoratorItemPrivate::execute()
{
    Q_CHECK_PTR(childItems[0]);
    Q_ASSERT(Ghost::Invalid != status);
    Q_ASSERT(Ghost::Running != status);

    setStatus(Ghost::Running);

    executeChildItem();
}

void GDecoratorItemPrivate::terminate()
{
    Q_CHECK_PTR(childItems[0]);
    Q_ASSERT(Ghost::Running == status);

    dptr(childItems[0])->terminate();
}

void GDecoratorItemPrivate::setSuccessIfPreconditionFalse()
{
    Q_CHECK_PTR(childItems[0]);
    Q_ASSERT(Ghost::Running == status);

    GGhostItemPrivate *childptr = dptr(childItems[0]);
    if (childptr->callPrecondition()) {
        childptr->execute();
    } else {
        setStatus(Ghost::Success);
    }
}

void GDecoratorItemPrivate::setFailureIfPreconditionFalse()
{
    Q_CHECK_PTR(childItems[0]);
    Q_ASSERT(Ghost::Running == status);

    GGhostItemPrivate *childptr = dptr(childItems[0]);
    if (childptr->callPrecondition()) {
        childptr->execute();
    } else {
        setStatus(Ghost::Failure);
    }
}
