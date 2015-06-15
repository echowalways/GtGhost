#ifndef GBLACKBOARD_P_P_H
#define GBLACKBOARD_P_P_H

#include <private/qobject_p.h>

#include "gblackboard_p.h"

// class GBlackboardPrivate

class GBlackboardPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(GBlackboard)

public:
    GBlackboardPrivate();
    virtual ~GBlackboardPrivate();

private:
    QHash<QString, QJSValue> datas;
};

// class GBlackboardAttachedPrivate

class GBlackboardAttachedPrivate : public GBlackboardPrivate
{
    Q_DECLARE_PUBLIC(GBlackboardAttached)

public:
    GBlackboardAttachedPrivate();
    virtual ~GBlackboardAttachedPrivate();

private:
    GGhostTree *masterTree;
    GGhostNode *targetNode;

private:
    GBlackboardAttached *sharedBlackboard(bool create = true) const;
    GBlackboardAttached *scopedBlackboard(bool create = true) const;
private:
    GBlackboardAttached *sharedBlackboardAttached;
    GBlackboardAttached *scopedBlackboardAttached;
};

// class GBlackboardGlobalPrivate

class GBlackboardGlobalPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(GBlackboardGlobal)

public:
    GBlackboardGlobalPrivate();
    virtual ~GBlackboardGlobalPrivate();

private:
    typedef QPointer<GBlackboardAttached> Blackboard;
    QHash<QQmlEngine *, Blackboard> blackboards;
};

#endif // GBLACKBOARD_P_P_H

