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

private:
    virtual Ghost::ItemType itemType() const Q_DECL_FINAL;
};

#endif // GINVERTERITEM_H
