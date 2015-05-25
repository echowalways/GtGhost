#ifndef GRANDOMSELECTORITEM_H
#define GRANDOMSELECTORITEM_H

#include "gcompositeitem.h"

class GRandomSelectorItemPrivate;
class GRandomSelectorItem : public GCompositeItem
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GRandomSelectorItem)
    Q_PROPERTY(Ghost::UpdateMode updateMode READ updateMode WRITE setUpdateMode)
    Q_PROPERTY(Ghost::RandomMode randomMode READ randomMode WRITE setRandomMode)

public:
    explicit GRandomSelectorItem(QObject *parent = 0);

public:
    void setRandomMode(Ghost::RandomMode mode);
    Ghost::RandomMode randomMode() const;
};

#endif // GRANDOMSELECTORITEM_H
