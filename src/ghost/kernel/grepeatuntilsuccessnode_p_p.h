#ifndef GREPEATUNTILSUCCESSNODE_P_P_H
#define GREPEATUNTILSUCCESSNODE_P_P_H

#include "gdecoratornode_p_p.h"
#include "grepeatuntilsuccessnode_p.h"

class GRepeatUntilSuccessNodePrivate : GDecoratorNodePrivate
{
    Q_DECLARE_PUBLIC(GRepeatUntilSuccessNode)

public:
    GRepeatUntilSuccessNodePrivate();
    virtual ~GRepeatUntilSuccessNodePrivate();

protected:
    virtual void onChildStatusChanged(GGhostSourceNode *childNode) Q_DECL_FINAL;

private:
    int loopCount;
    int loopCounter;
};

#endif // GREPEATUNTILSUCCESSNODE_P_P_H
