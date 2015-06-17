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
    GGhostTree *masterTree;
    GGhostNode *targetNode;

    GBlackboard *globalBlackboard;
    GBlackboard *sharedBlackboard;

private:
    QHash<QString, QJSValue> datas;
};

#endif // GBLACKBOARD_P_P_H

