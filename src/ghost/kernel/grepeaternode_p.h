#ifndef GREPEATERNODE_P_H
#define GREPEATERNODE_P_H

#include "gdecoratornode_p.h"

class GRepeaterNodePrivate;
class GRepeaterNode : public GDecoratorNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GRepeaterNode)
    Q_PROPERTY(int loopCount READ loopCount WRITE setLoopCount NOTIFY loopCountChanged)

public:
    explicit GRepeaterNode(QObject *parent = 0);

Q_SIGNALS:
    void loopCountChanged(int value);
public:
    void setLoopCount(int value);
    int loopCount() const;
};

#endif // GREPEATERNODE_P_H
