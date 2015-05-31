#ifndef GGHOSTSOURCENODE_P_P_H
#define GGHOSTSOURCENODE_P_P_H

#include <private/qobject_p.h>

#include "gghostsourcenode_p.h"

class GGhostSourceNodePrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(GGhostSourceNode)

public:
    GGhostSourceNodePrivate();
    virtual ~GGhostSourceNodePrivate();

public:
    GGhostSourceNode *parentSourceNode;

public:
    static const char *toString(Ghost::Status status);
    void setStatus(Ghost::Status status);
public:
    Ghost::Status status;

protected:
    virtual void onStatusChanged(Ghost::Status status);
    virtual void onChildStatusChanged(GGhostSourceNode *childNode);

public:
    static GGhostSourceNodePrivate *cast(GGhostSourceNode *node) { return node->d_func(); }
    static const GGhostSourceNodePrivate *cast(const GGhostSourceNode *node) { return node->d_func(); }

public:
    virtual bool initialize() = 0;

    virtual void reset() = 0;
    virtual void execute() = 0;
    virtual void terminate() = 0;

public:
    QString summary;
};

#endif // GGHOSTSOURCENODE_P_P_H
