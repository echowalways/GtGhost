#ifndef GRANDOMSEQUENCEITEM_H
#define GRANDOMSEQUENCEITEM_H

#include "gcompositeitem.h"

class GRandomSequenceItemPrivate;
class GRandomSequenceItem : public GCompositeItem
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GRandomSequenceItem)
    Q_PROPERTY(Ghost::UpdateMode updateMode READ updateMode WRITE setUpdateMode)
    Q_PROPERTY(Ghost::RandomMode randomMode READ randomMode WRITE setRandomMode)

public:
    explicit GRandomSequenceItem(QObject *parent = 0);

public:
    void setRandomMode(Ghost::RandomMode mode);
    Ghost::RandomMode randomMode() const;
};

#endif // GRANDOMSEQUENCEITEM_H
