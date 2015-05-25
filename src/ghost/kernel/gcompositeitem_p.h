#ifndef GCOMPOSITEITEM_P_H
#define GCOMPOSITEITEM_P_H

#include "gghostitem_p.h"
#include "gcompositeitem.h"

class GCompositeItemPrivate : public GGhostItemPrivate
{
    Q_DECLARE_PUBLIC(GCompositeItem)

public:
    enum LinearMode {
        Sequence,
        Selector
    };

public:
    explicit GCompositeItemPrivate(LinearMode mode);
    virtual ~GCompositeItemPrivate();

public:
    virtual bool initialize() Q_DECL_FINAL;

public:
    virtual void reset() Q_DECL_FINAL;
    virtual void execute() Q_DECL_FINAL;
    virtual void terminate() Q_DECL_FINAL;

public:
    virtual void onChildStatusChanged(GGhostItem *child, Ghost::Status status) Q_DECL_FINAL;

public:
    LinearMode linearMode;
    Ghost::UpdateMode updateMode;

public:
    virtual void updateChildItems() = 0;
    virtual GGhostItemList &sortedChildItems() = 0;

private:
    void executeNextChildItem();
private:
    int seekIndex;
};

#endif // GCOMPOSITEITEM_P_H
