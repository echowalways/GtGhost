#ifndef GPARALLELNODE_P_P_H
#define GPARALLELNODE_P_P_H

#include "gcompositenode_p_p.h"
#include "gparallelnode_p.h"

class GParallelNodePrivate : public GCompositeNodePrivate
{
    Q_DECLARE_PUBLIC(GParallelNode)

public:
    GParallelNodePrivate();
    virtual ~GParallelNodePrivate();

private:
    virtual void confirmEvent(GGhostConfirmEvent *event) Q_DECL_FINAL;

public:
    virtual void execute() Q_DECL_FINAL;
    virtual void terminate() Q_DECL_FINAL;

private:
    bool executeState;
    bool terminateState;
};

#endif // GPARALLELNODE_P_P_H

