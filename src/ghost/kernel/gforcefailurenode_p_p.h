#ifndef GFORCEFAILURENODE_P_P_H
#define GFORCEFAILURENODE_P_P_H

#include "gdecoratornode_p_p.h"
#include "gforcefailurenode_p.h"

class GForceFailureNodePrivate : public GDecoratorNodePrivate
{
    Q_DECLARE_PUBLIC(GForceFailureNode)

public:
    GForceFailureNodePrivate();
    virtual ~GForceFailureNodePrivate();

protected:
    virtual void onChildStatusChanged(GGhostSourceNode *childNode) Q_DECL_FINAL;
};

#endif // GFORCEFAILURENODE_P_P_H
