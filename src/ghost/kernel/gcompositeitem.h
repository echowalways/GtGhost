#ifndef GCOMPOSITEITEM_H
#define GCOMPOSITEITEM_H

#include "gghostitem.h"

class GCompositeItemPrivate;
class GCompositeItem : public GGhostItem
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GCompositeItem)

protected:
    GCompositeItem(GCompositeItemPrivate &dd, QObject *parent);

private:
    virtual Ghost::NodeType nodeType() const Q_DECL_FINAL;

public:
    void setUpdateMode(Ghost::UpdateMode mode);
    Ghost::UpdateMode updateMode() const;
};

#endif // GCOMPOSITEITEM_H
