#ifndef GGHOSTTREE_P_H
#define GGHOSTTREE_P_H

#include "gghostnode_p.h"
#include "gghosttree.h"

class GGhostItemPrivate;

class GGhostTreePrivate : public GGhostNodePrivate
{
    Q_DECLARE_PUBLIC(GGhostTree)

public:
    GGhostTreePrivate();
    virtual ~GGhostTreePrivate();

public:
    static GGhostItemPrivate *dptr(GGhostItem *item);
    static const GGhostItemPrivate *dptr(const GGhostItem *item);

public:
    virtual bool initialize() Q_DECL_FINAL;

    virtual void reset() Q_DECL_FINAL;
    virtual void execute() Q_DECL_FINAL;
    virtual void terminate() Q_DECL_FINAL;

public:
    virtual void onStatusChanged(Ghost::Status status) Q_DECL_FINAL;
    virtual void onChildStatusChanged(GGhostItem *child, Ghost::Status status) Q_DECL_FINAL;

private:
    QHash<QString, QJSValue> runtimeVariables;
};

#endif // GGHOSTTREE_P_H

