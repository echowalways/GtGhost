#ifndef GGHOSTNODE_P_H
#define GGHOSTNODE_P_H

#include <private/qobject_p.h>
#include <QtQml/QQmlListProperty>

#include "gghostnode.h"

class GGhostNodePrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(GGhostNode)

public:
    GGhostNodePrivate();
    virtual ~GGhostNodePrivate();

public:
    static GGhostNodePrivate *dptr(GGhostNode *node) { return node->d_func(); }
    static const GGhostNodePrivate *dptr(const GGhostNode *node) { return node->d_func(); }

public:
    GGhostTree *parentTree;
    GGhostNode *parentNode;

public:
    QQmlListProperty<GGhostItem> ghostItems();
public:
    GGhostItemList childItems;

public:
    static const char *toString(Ghost::Status status);
    void setStatus(Ghost::Status status);
public:
    Ghost::Status status;

public:
    virtual bool initialize() = 0;

    virtual void reset() = 0;
    virtual void execute() = 0;
    virtual void terminate() = 0;

public:
    virtual void onStatusChanged(Ghost::Status status);
    virtual void onChildStatusChanged(GGhostItem *child, Ghost::Status status);

public:
    QString description;
};

#endif // GGHOSTNODE_P_H

