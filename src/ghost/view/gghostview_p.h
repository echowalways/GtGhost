#ifndef GGHOSTVIEW_P_H
#define GGHOSTVIEW_P_H

#include <private/qquickitem_p.h>

#include "gghostview.h"
#include "gghostviewitem.h"

class GGhostViewPrivate : public QQuickItemPrivate
{
    Q_DECLARE_PUBLIC(GGhostView)

public:
    GGhostViewPrivate();
    virtual ~GGhostViewPrivate();

private:
    QPointer<QObject> target;
    QPointer<QQmlComponent> itemDelegate;
    QPointer<QQmlComponent> lineDelegate;
    QPointer<GGhostViewItem> rootViewItem;

private:
    void createItems();
    GGhostViewItem *createItems(GGhostItem *ghostItem, QQuickItem *parentViewItem);
    void buildLayout();

    QSize buildLayout(GGhostViewItem *viewItem, bool &hasCompositeNode);
};

#endif // GGHOSTVIEW_P_H
