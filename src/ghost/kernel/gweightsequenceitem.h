#ifndef GWEIGHTSEQUENCEITEM_H
#define GWEIGHTSEQUENCEITEM_H

#include "gcompositeitem.h"

class GWeightSequenceItemPrivate;
class GWeightSequenceItem : public GCompositeItem
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GWeightSequenceItem)
    Q_PROPERTY(Ghost::UpdateMode updateMode READ updateMode WRITE setUpdateMode)

public:
    explicit GWeightSequenceItem(QObject *parent = 0);
};

#endif // GWEIGHTSEQUENCEITEM_H
