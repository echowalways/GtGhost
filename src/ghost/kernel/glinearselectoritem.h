#ifndef GLINEARSELECTORITEM_H
#define GLINEARSELECTORITEM_H

#include "gcompositeitem.h"

class GLinearSelectorItemPrivate;
class GLinearSelectorItem : public GCompositeItem
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GLinearSelectorItem)

public:
    explicit GLinearSelectorItem(QObject *parent = 0);

private:
    virtual Ghost::ItemType itemType() const Q_DECL_FINAL;
};

#endif // GLINEARSELECTORITEM_H
