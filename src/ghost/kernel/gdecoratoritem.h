#ifndef GDECORATORITEM_H
#define GDECORATORITEM_H

#include "gghostitem.h"

class GDecoratorItemPrivate;
class GDecoratorItem : public GGhostItem
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GDecoratorItem)

protected:
    GDecoratorItem(GDecoratorItemPrivate &dd, QObject *parent);
};

#endif // GDECORATORITEM_H
