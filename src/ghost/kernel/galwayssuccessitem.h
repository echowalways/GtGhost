#ifndef GALWAYSSUCCESSITEM_H
#define GALWAYSSUCCESSITEM_H

#include "gdecoratoritem.h"

class GAlwaysSuccessItemPrivate;
class GAlwaysSuccessItem : public GDecoratorItem
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GAlwaysSuccessItem)

public:
    explicit GAlwaysSuccessItem(QObject *parent = 0);

private:
    virtual Ghost::ItemType itemType() const Q_DECL_FINAL;
};

#endif // GALWAYSSUCCESSITEM_H
