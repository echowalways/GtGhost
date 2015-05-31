#ifndef GFORCESUCCESSNODE_P_H
#define GFORCESUCCESSNODE_P_H

#include "gdecoratornode_p.h"

class GForceSuccessNodePrivate;
class GForceSuccessNode : public GDecoratorNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GForceSuccessNode)

public:
    explicit GForceSuccessNode(QObject *parent = 0);
};

#endif // GFORCESUCCESSNODE_P_H
