#ifndef GCOMPOSITENODE_P_P_H
#define GCOMPOSITENODE_P_P_H

#include "gghostnode_p_p.h"
#include "gcompositenode_p.h"

class GCompositeNodePrivate : public GGhostNodePrivate
{
    Q_DECLARE_PUBLIC(GCompositeNode)

public:
    explicit GCompositeNodePrivate(Ghost::NodeType nodeType);
    virtual ~GCompositeNodePrivate();

public:
    Ghost::Status breakStatus;

    int unmatchCount;
    int unmatchCounter;
    int executeIndex;
    int executeCounter;
};

#endif // GCOMPOSITENODE_P_P_H

