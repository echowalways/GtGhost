#ifndef GFORCEFAILURENODE_P_H
#define GFORCEFAILURENODE_P_H

#include "gdecoratornode_p.h"

class GForceFailureNodePrivate;
class GForceFailureNode : public GDecoratorNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GForceFailureNode)

public:
    explicit GForceFailureNode(QObject *parent = 0);
};

#endif // GFORCEFAILURENODE_P_H
