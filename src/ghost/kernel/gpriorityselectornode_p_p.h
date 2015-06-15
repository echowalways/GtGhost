#ifndef GPRIORITYSELECTORNODE_P_P_H
#define GPRIORITYSELECTORNODE_P_P_H

#include "gcompositenode_p_p.h"
#include "gpriorityselectornode_p.h"

class GPrioritySelectorNodePrivate : public GCompositeNodePrivate
{
    Q_DECLARE_PUBLIC(GPrioritySelectorNode)

public:
    GPrioritySelectorNodePrivate();
    virtual ~GPrioritySelectorNodePrivate();

private:
    virtual void confirmEvent(GGhostConfirmEvent *event) Q_DECL_FINAL;

public:
    virtual void reset() Q_DECL_FINAL;
    virtual void execute() Q_DECL_FINAL;
    virtual void terminate() Q_DECL_FINAL;

private:
    void executeNextChildNode();

private:
    void resortChildNodes();
private:
    Ghost::UpdateMode updateMode;
    GGhostNodeList sortedChildNodes;
};

#endif // GPRIORITYSELECTORNODE_P_P_H

