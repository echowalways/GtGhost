#ifndef GBLACKBOARD_P_P_H
#define GBLACKBOARD_P_P_H

#include <private/qobject_p.h>

#include "gblackboard_p.h"

class GBlackboardPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(GBlackboard)

public:
    GBlackboardPrivate();
    virtual ~GBlackboardPrivate();

private:
    QHash<QString, QJSValue> datas;
};

class GBlackboardAttachedPrivate : public GBlackboardPrivate
{
    Q_DECLARE_PUBLIC(GBlackboardAttached)

public:
    GBlackboardAttachedPrivate();
    virtual ~GBlackboardAttachedPrivate();

private:
    GGhostTree *masterTree;
    GGhostNode *targetNode;
};

#endif // GBLACKBOARD_P_P_H

