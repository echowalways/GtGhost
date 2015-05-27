#ifndef GGHOSTVIEWITEM_P_H
#define GGHOSTVIEWITEM_P_H

#include <private/qquickitem_p.h>

#include "gghostviewitem.h"
#include "gghostitem.h"

class GGhostViewItemPrivate : public QQuickItemPrivate
{
    Q_DECLARE_PUBLIC(GGhostViewItem)

public:
    GGhostViewItemPrivate();
    virtual ~GGhostViewItemPrivate();

public:
    static GGhostViewItemPrivate *dptr(GGhostViewItem *item) { return item->d_func(); }
    static const GGhostViewItemPrivate *dptr(const GGhostViewItem *item) { return item->d_func(); }

public:
    QPointer<GGhostItem> target;
    QList<GGhostViewItem *> childViewItems;
};

#endif // GGHOSTVIEWITEM_P_H
