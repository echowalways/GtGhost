#ifndef GLEAFNODE_H
#define GLEAFNODE_H

#include "gghostnode_p.h"

class GLeafNodePrivate;
class GLeafNode : public GGhostNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GLeafNode)

protected:
    explicit GLeafNode(GLeafNodePrivate &dd, QObject *parent);
};

#endif // GLEAFNODE_H
