#ifndef GINVERTERNODE_P_P_H
#define GINVERTERNODE_P_P_H

#include "gdecoratornode_p_p.h"
#include "ginverternode_p.h"

class GInverterNodePrivate : public GDecoratorNodePrivate
{
    Q_DECLARE_PUBLIC(GInverterNode)

public:
    GInverterNodePrivate();
    virtual ~GInverterNodePrivate();

private:
    virtual void confirmEvent(GGhostConfirmEvent *event) Q_DECL_FINAL;
};

#endif // GINVERTERNODE_P_P_H
