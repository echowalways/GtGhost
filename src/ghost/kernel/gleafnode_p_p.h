#ifndef GLEAFNODE_P_P_H
#define GLEAFNODE_P_P_H

#include "gghostnode_p_p.h"
#include "gleafnode_p.h"

class GLeafNodePrivate : public GGhostNodePrivate
{
    Q_DECLARE_PUBLIC(GLeafNode)

public:
    explicit GLeafNodePrivate(Ghost::NodeType nodeType);
    virtual ~GLeafNodePrivate();
};

#endif // GLEAFNODE_P_P_H

