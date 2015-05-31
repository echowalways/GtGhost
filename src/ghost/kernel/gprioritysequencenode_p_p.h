#ifndef GPRIORITYSEQUENCENODE_P_P_H
#define GPRIORITYSEQUENCENODE_P_P_H

#include "gcompositenode_p_p.h"
#include "gprioritysequencenode_p.h"

class GPrioritySequenceNodePrivate : public GCompositeNodePrivate
{
    Q_DECLARE_PUBLIC(GPrioritySequenceNode)

public:
    GPrioritySequenceNodePrivate();
    virtual ~GPrioritySequenceNodePrivate();

protected:
    virtual void onChildStatusChanged(GGhostSourceNode *childNode) Q_DECL_FINAL;

public:
    virtual bool initialize() Q_DECL_FINAL;

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

#endif // GPRIORITYSEQUENCENODE_P_P_H

