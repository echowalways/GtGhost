#include "gghostview.h"
#include "gghostview_p.h"

#include <QtCore/QLoggingCategory>
#include <QtQml/QQmlEngine>

#include "gghosttree.h"
#include "gghostitem.h"
#include "gghostviewitem.h"
#include "gghostviewitem_p.h"

Q_LOGGING_CATEGORY(qlcGhostView, "GtGhost.GhostView")

// class GGhostView

GGhostView::GGhostView(QQuickItem *parent)
    : QQuickItem(*new GGhostViewPrivate(), parent)
{
}

void GGhostView::classBegin()
{
    QQuickItem::classBegin();
}

void GGhostView::componentComplete()
{
    Q_D(GGhostView);

    QQuickItem::componentComplete();

    d->createItems();
    d->buildLayout();
}

void GGhostView::setTarget(QObject *value)
{
    Q_D(GGhostView);

    if(d->target != value) {
        d->target = value;
        emit targetChanged(value);
    }
}

void GGhostView::setItemDelegate(QQmlComponent *value)
{
    Q_D(GGhostView);

    if(d->itemDelegate != value) {
        d->itemDelegate = value;
        emit itemDelegateChanged(value);
    }
}

void GGhostView::setLineDelegate(QQmlComponent *value)
{
    Q_D(GGhostView);

    if(d->lineDelegate != value) {
        d->lineDelegate = value;
        emit lineDelegateChanged(value);
    }
}

QObject *GGhostView::target() const
{
    Q_D(const GGhostView);
    return d->target.data();
}

QQmlComponent *GGhostView::itemDelegate() const
{
    Q_D(const GGhostView);
    return d->itemDelegate.data();
}

QQmlComponent *GGhostView::lineDelegate() const
{
    Q_D(const GGhostView);
    return d->lineDelegate.data();
}

// class GGhostViewPrivate

GGhostViewPrivate::GGhostViewPrivate()
{
}

GGhostViewPrivate::~GGhostViewPrivate()
{
}

void GGhostViewPrivate::createItems()
{
    if (!target) {
        return;
    }

    GGhostItem *item
            = qobject_cast<GGhostItem *>(target.data());
    if (nullptr == item) {
        GGhostTree *tree
                = qobject_cast<GGhostTree *>(target.data());
        if (tree) {
            item = tree->childItems().value(0);
        }
    }
    if (nullptr == item) {
        return;
    }

    rootViewItem = createItems(item, q_func());
}

GGhostViewItem *GGhostViewPrivate::createItems(GGhostItem *ghostItem, QQuickItem *parentViewItem)
{
    Q_ASSERT(!itemDelegate.isNull());

    QObject *viewObject = itemDelegate->beginCreate(QQmlEngine::contextForObject(q_func()));
    if (nullptr == viewObject) {
        return nullptr;
    }

    GGhostViewItem *viewItem
            = qobject_cast<GGhostViewItem *>(viewObject);
    if (nullptr == viewItem) {
        return nullptr;
    }

    viewItem->setTarget(ghostItem);
    itemDelegate->completeCreate();

    if (!ghostItem->childItems().isEmpty()) {
        GGhostViewItemPrivate *dptr
                = GGhostViewItemPrivate::dptr(viewItem);

        Q_FOREACH (GGhostItem *childGhostItem, ghostItem->childItems()) {
            GGhostViewItem *childViewItem
                    = createItems(childGhostItem, viewItem);
            if (childViewItem) {
                dptr->childViewItems << childViewItem;
            }
        }
    }

    viewItem->setParentItem(parentViewItem);

    return viewItem;
}

void GGhostViewPrivate::buildLayout()
{
    if (!rootViewItem) {
        return;
    }

    bool hasCompositeNode = false;
    QSize size = buildLayout(rootViewItem.data(), hasCompositeNode);
    q_func()->setWidth(size.width());
    q_func()->setHeight(size.height());
    rootViewItem->setX(size.width() / 2);
    qDebug() << "size" << size;
}

QSize GGhostViewPrivate::buildLayout(GGhostViewItem *viewItem, bool &hasCompositeNode)
{
    GGhostItem *item = viewItem->target();

    switch (item->nodeType()) {
    case Ghost::CompositeNode:
        break;
    case Ghost::DecoratorNode:
        break;
    case Ghost::ConditionNode:
        break;
    case Ghost::ActionNode:
        break;
    default:
        Q_UNREACHABLE();
    }

    if ((item->nodeType() == Ghost::ActionNode)
            || (item->nodeType() == Ghost::ConditionNode)) {
        return QSize(viewItem->width(), viewItem->height());
    } else if (item->nodeType() == Ghost::DecoratorNode)  {
        GGhostViewItemPrivate *dptr
                = GGhostViewItemPrivate::dptr(viewItem);

        GGhostViewItem *childViewItem
                = dptr->childViewItems.value(0);
        if (!childViewItem) {
            return QSize(viewItem->width(), viewItem->height());
        }
        qDebug("BBB");

        bool hasCompositeNode2 = false;
        QSize size = buildLayout(childViewItem, hasCompositeNode2);
        if (hasCompositeNode2) {
            hasCompositeNode = true;
        }
        if (hasCompositeNode2) {
            int w = qMax(int(viewItem->width()), size.width());
            int h = viewItem->height() + 5 + size.height();
            return QSize(w, h);
        } else {
            int w = viewItem->width() + 5 + size.width();
            int h = qMax(int(viewItem->height()), size.height());
            return QSize(w, h);
        }
        return QSize(0, 0);
    } else if (item->nodeType() == Ghost::CompositeNode)  {

        GGhostViewItemPrivate *dptr
                = GGhostViewItemPrivate::dptr(viewItem);
        int xx = 0;
        int www = 0;
        QHash<void *, QSize> sizes;
        Q_FOREACH(GGhostViewItem *childViewItem, dptr->childViewItems) {
            bool hasCompositeNode2 = false;
            QSize size = buildLayout(childViewItem, hasCompositeNode2);
            sizes.insert(childViewItem, size);
            www += size.width() + 10;

            if (hasCompositeNode2) {
                hasCompositeNode = true;
            }
        }

        www = www / 2;

        if (hasCompositeNode) {
            int x = -www;
            int y = viewItem->height() + 10;
            int maxY = 0;
            Q_FOREACH(GGhostViewItem *childViewItem, dptr->childViewItems) {
                QSize size = sizes.value(childViewItem);
                childViewItem->setX(x);
                childViewItem->setY(y);

                x += size.width() + 10;
                maxY = qMax(size.height(), maxY);
            }
            hasCompositeNode = true;
            return QSize(x - 10, y + maxY);
        } else {
            int offset = viewItem->width() / 2;
            int y = 0;
            int maxX = viewItem->width();
            Q_FOREACH(GGhostViewItem *childViewItem, dptr->childViewItems) {
                QSize size = sizes.value(childViewItem);
                childViewItem->setX(offset - size.width() / 2);
                childViewItem->setY(y);

                y += size.height() + 10;
                maxX = qMax(size.width(), maxX);
            }
            hasCompositeNode = true;
            return QSize(maxX, y - 10);
        }

        return QSize(xx, viewItem->height() + 10 + 100);
    }

    Q_UNREACHABLE();
    return QSize(-1, -1);
}
