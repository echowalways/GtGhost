#ifndef GRANDOMSEQUENCENODE_P_P_H
#define GRANDOMSEQUENCENODE_P_P_H

#include "gcompositenode_p_p.h"
#include "grandomsequencenode_p_p.h"

class GRandomSequenceNodePrivate : public GCompositeNodePrivate
{
    Q_DECLARE_PUBLIC(GRandomSequenceNode)

public:
    GRandomSequenceNodePrivate();
    virtual ~GRandomSequenceNodePrivate();

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
    Ghost::RandomMode randomMode;
};

#endif // GRANDOMSEQUENCENODE_P_P_H

