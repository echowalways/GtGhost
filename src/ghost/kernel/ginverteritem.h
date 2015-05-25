#ifndef GINVERTERITEM_H
#define GINVERTERITEM_H

#include "gdecoratoritem.h"

class GInverterItemPrivate;
class GInverterItem : public GDecoratorItem
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GInverterItem)

public:
    explicit GInverterItem(QObject *parent = 0);
};

#endif // GINVERTERITEM_H
