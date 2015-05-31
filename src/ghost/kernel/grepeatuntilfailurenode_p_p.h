#ifndef GREPEATUNTILFAILURENODE_P_P_H
#define GREPEATUNTILFAILURENODE_P_P_H

#include "gdecoratornode_p_p.h"
#include "grepeatuntilfailurenode_p.h"

class GRepeatUntilFailureNodePrivate : public GDecoratorNodePrivate
{
    Q_DECLARE_PUBLIC(GRepeatUntilFailureNode)

public:
    GRepeatUntilFailureNodePrivate();
    virtual ~GRepeatUntilFailureNodePrivate();

protected:
    virtual void onChildStatusChanged(GGhostSourceNode *childNode) Q_DECL_FINAL;

private:
    int loopCount;
    int loopCounter;
};

#endif // GREPEATUNTILFAILURENODE_P_P_H
