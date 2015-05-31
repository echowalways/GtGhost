#ifndef GPARALLELNODE_P_H
#define GPARALLELNODE_P_H

#include "gcompositenode_p.h"

class GParallelNodePrivate;
class GParallelNode : public GCompositeNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GParallelNode)

public:
    explicit GParallelNode(QObject *parent = 0);
};

#endif // GPARALLELNODE_P_H
