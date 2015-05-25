#ifndef GLINEARCOMPOSITEITEM_H
#define GLINEARCOMPOSITEITEM_H

#include "gghostitem.h"

class GLinearCompositeItemPrivate;
class GLinearCompositeItem : public GGhostItem
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GLinearCompositeItem)
    Q_PROPERTY(UpdateMode updateMode READ updateMode WRITE setUpdateMode)
    Q_ENUMS(UpdateMode)

protected:
    GLinearCompositeItem(GLinearCompositeItemPrivate &dd, QObject *parent);

public:
    enum UpdateMode {
        ResetOnly,
        Everytime
    };

public:
    void setUpdateMode(UpdateMode mode);
    UpdateMode updateMode() const;
};

#endif // GLINEARCOMPOSITEITEM_H
