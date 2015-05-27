#ifndef GIDLEACTIONITEM_H
#define GIDLEACTIONITEM_H

#include "gghostitem.h"

class GIdleActionItemPrivate;
class GIdleActionItem : public GGhostItem
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GIdleActionItem)
    Q_PROPERTY(int duration READ duration WRITE setDuration NOTIFY durationChanged)

public:
    explicit GIdleActionItem(QObject *parent = 0);

private:
    virtual Ghost::NodeType nodeType() const Q_DECL_FINAL;
    virtual Ghost::ItemType itemType() const Q_DECL_FINAL;

Q_SIGNALS:
    void durationChanged(int value);
public:
    void setDuration(int value);
    int duration() const;

private:
    Q_PRIVATE_SLOT(d_func(), void onTimeout())
};

#endif // GIDLEACTIONITEM_H
