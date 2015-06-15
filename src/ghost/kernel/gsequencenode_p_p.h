#ifndef GSEQUENCENODE_P_P_H
#define GSEQUENCENODE_P_P_H

#include "gcompositenode_p_p.h"
#include "gsequencenode_p.h"

class GSequenceNodePrivate : public GCompositeNodePrivate
{
    Q_DECLARE_PUBLIC(GSequenceNode)

public:
    GSequenceNodePrivate();
    virtual ~GSequenceNodePrivate();

private:
    virtual void confirmEvent(GGhostConfirmEvent *event) Q_DECL_FINAL;

public:
    virtual void reset() Q_DECL_FINAL;
    virtual void execute() Q_DECL_FINAL;
    virtual void terminate() Q_DECL_FINAL;

private:
    void executeNextChildNode();
};

#endif // GSEQUENCENODE_P_P_H

