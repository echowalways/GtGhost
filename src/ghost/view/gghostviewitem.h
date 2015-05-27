#ifndef GGHOSTVIEWITEM_H
#define GGHOSTVIEWITEM_H

#include <QtQuick/QQuickItem>

class GGhostItem;

class GGhostViewItemPrivate;
class GGhostViewItem : public QQuickItem
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GGhostViewItem)
    Q_PROPERTY(GGhostItem* target READ target NOTIFY targetChanged)

public:
    explicit GGhostViewItem(QQuickItem *parent = 0);

Q_SIGNALS:
    void targetChanged(GGhostItem *target);
public:
    void setTarget(GGhostItem *target);
    GGhostItem *target() const;
};

#endif // GGHOSTVIEWITEM_H
