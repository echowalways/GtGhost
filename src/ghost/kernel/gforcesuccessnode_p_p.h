#ifndef GFORCESUCCESSNODE_P_P_H
#define GFORCESUCCESSNODE_P_P_H

#include "gdecoratornode_p_p.h"
#include "gforcesuccessnode_p.h"

class GForceSuccessNodePrivate : public GDecoratorNodePrivate
{
    Q_DECLARE_PUBLIC(GForceSuccessNode)

public:
    GForceSuccessNodePrivate();
    virtual ~GForceSuccessNodePrivate();

protected:
    virtual void onChildStatusChanged(GGhostSourceNode *childNode) Q_DECL_FINAL;
};

#endif // GFORCESUCCESSNODE_P_P_H
