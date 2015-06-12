#ifndef GREPEATERNODE_P_P_H
#define GREPEATERNODE_P_P_H

#include "gdecoratornode_p_p.h"
#include "grepeaternode_p.h"

class GRepeaterNodePrivate : public GDecoratorNodePrivate
{
    Q_DECLARE_PUBLIC(GRepeaterNode)

public:
    GRepeaterNodePrivate();
    virtual ~GRepeaterNodePrivate();

private:
    virtual void confirmEvent(GGhostConfirmEvent *event) Q_DECL_FINAL;

private:
    int loopCount;
    int loopCounter;
};

#endif // GREPEATERNODE_P_P_H
