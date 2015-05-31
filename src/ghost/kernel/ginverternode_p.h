#ifndef GINVERTERNODE_P_H
#define GINVERTERNODE_P_H

#include "gdecoratornode_p.h"

class GInverterNodePrivate;
class GInverterNode : public GDecoratorNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GInverterNode)

public:
    explicit GInverterNode(QObject *parent = 0);
};

#endif // GINVERTERNODE_P_H
