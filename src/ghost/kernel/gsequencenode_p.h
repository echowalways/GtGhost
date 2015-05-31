#ifndef GSEQUENCENODE_P_H
#define GSEQUENCENODE_P_H

#include "gcompositenode_p.h"

class GSequenceNodePrivate;
class GSequenceNode : public GCompositeNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GSequenceNode)

public:
    explicit GSequenceNode(QObject *parent = 0);
};

#endif // GSEQUENCENODE_P_H
