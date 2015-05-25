#ifndef GGHOSTITEM_P_H
#define GGHOSTITEM_P_H

#include <QtQml/QJSValue>

#include "gghostnode_p.h"
#include "gghostitem.h"

class GGhostItemPrivate : public GGhostNodePrivate
{
    Q_DECLARE_PUBLIC(GGhostItem)

public:
    GGhostItemPrivate();
    virtual ~GGhostItemPrivate();

public:
    static GGhostItemPrivate *dptr(GGhostItem *item) { return item->d_func(); }
    static const GGhostItemPrivate *dptr(const GGhostItem *item) { return item->d_func(); }

public:
    void sync(GGhostTree *parentTree, GGhostNode *parentNode);

private:
    QJSValue precondition;
    QJSValue weight;

public:
    bool callPrecondition();
    uint callWeight();

public:
    int orderedValue;
public:
    static void sort(GGhostItemList &items);
    static bool itemGreatThan(GGhostItem *lhs, GGhostItem *rhs);
};

#endif // GGHOSTITEM_P_H

