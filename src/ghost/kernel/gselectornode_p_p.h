#ifndef GSELECTORNODE_P_P_H
#define GSELECTORNODE_P_P_H

#include "gcompositenode_p_p.h"
#include "gselectornode_p.h"

class GSelectorNodePrivate : public GCompositeNodePrivate
{
    Q_DECLARE_PUBLIC(GSelectorNode)

public:
    GSelectorNodePrivate();
    virtual ~GSelectorNodePrivate();

private:
    virtual void confirmEvent(GGhostConfirmEvent *event) Q_DECL_FINAL;

public:
    virtual void reset() Q_DECL_FINAL;
    virtual void execute() Q_DECL_FINAL;
    virtual void terminate() Q_DECL_FINAL;

private:
    void executeNextChildNode();
};

#endif // GSELECTORNODE_P_P_H

