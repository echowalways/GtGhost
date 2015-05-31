#ifndef GSELECTORNODE_P_H
#define GSELECTORNODE_P_H

#include "gcompositenode_p.h"

class GSelectorNodePrivate;
class GSelectorNode : public GCompositeNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GSelectorNode)

public:
    explicit GSelectorNode(QObject *parent = 0);
};

#endif // GSELECTORNODE_P_H
