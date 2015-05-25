#ifndef GLINEARCOMPOSITEITEM_P_H
#define GLINEARCOMPOSITEITEM_P_H

#include "gghostitem_p.h"
#include "glinearcompositeitem.h"

class GLinearCompositeItemPrivate : public GGhostItemPrivate
{
    Q_DECLARE_PUBLIC(GLinearCompositeItem)

public:
    enum LinearMode {
        Sequence,
        Selector
    };

public:
    GLinearCompositeItemPrivate(LinearMode mode);
    virtual ~GLinearCompositeItemPrivate();

public:
    virtual void onChildStatusChanged(GGhostItem *childItem, GGhostNode::Status status) Q_DECL_FINAL;

public:
    virtual bool initialize() Q_DECL_FINAL;

public:
    virtual void reset() Q_DECL_FINAL;
    virtual void execute() Q_DECL_FINAL;
    virtual void terminate() Q_DECL_FINAL;

public:
    LinearMode linearMode;
    GLinearCompositeItem::UpdateMode updateMode;

public:
    virtual void updateChildItems() = 0;
    virtual GGhostItemList &sortedChildItems() = 0;

private:
    void executeNextChildItem();
private:
    int seekIndex;
};

#endif // GLINEARCOMPOSITEITEM_P_H
