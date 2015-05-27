#ifndef GWEIGHTSELECTORITEM_H
#define GWEIGHTSELECTORITEM_H

#include "gcompositeitem.h"

class GWeightSelectorItemPrivate;
class GWeightSelectorItem : public GCompositeItem
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GWeightSelectorItem)
    Q_PROPERTY(Ghost::UpdateMode updateMode READ updateMode WRITE setUpdateMode)

public:
    explicit GWeightSelectorItem(QObject *parent = 0);

private:
    virtual Ghost::ItemType itemType() const Q_DECL_FINAL;
};

#endif // GWEIGHTSELECTORITEM_H
