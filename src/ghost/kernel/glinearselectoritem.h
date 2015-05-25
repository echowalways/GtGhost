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
};

#endif // GLINEARSELECTORITEM_H
