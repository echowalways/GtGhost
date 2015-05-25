#ifndef GGHOSTUNITTEST_P_H
#define GGHOSTUNITTEST_P_H

#include <private/qobject_p.h>
#include <QtQml/QQmlListProperty>

#include "gghostunittest.h"
#include "gghosttree.h"

class GGhostUnitTestPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(GGhostUnitTest)

public:
    GGhostUnitTestPrivate();
    virtual ~GGhostUnitTestPrivate();

public:
    QQmlListProperty<GGhostTree> ghostTrees();
public:
    QList<GGhostTree *> childTrees;

public:
    QList<GGhostNode *> expectedStatusNodes;
    QList<Ghost::Status> expectedStatusValues;
};

#endif // GGHOSTUNITTEST_P_H

