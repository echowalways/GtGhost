#ifndef GLINEARSEQUENCEITEM_H
#define GLINEARSEQUENCEITEM_H

#include "gcompositeitem.h"

class GLinearSequenceItemPrivate;
class GLinearSequenceItem : public GCompositeItem
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GLinearSequenceItem)

public:
    explicit GLinearSequenceItem(QObject *parent = 0);
};

#endif // GLINEARSEQUENCEITEM_H
