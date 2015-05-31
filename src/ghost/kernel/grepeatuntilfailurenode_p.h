#ifndef GREPEATUNTILFAILURENODE_P_H
#define GREPEATUNTILFAILURENODE_P_H

#include "gdecoratornode_p.h"

class GRepeatUntilFailureNodePrivate;
class GRepeatUntilFailureNode : public GDecoratorNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GRepeatUntilFailureNode)
    Q_PROPERTY(int loopCount READ loopCount WRITE setLoopCount NOTIFY loopCountChanged)

public:
    explicit GRepeatUntilFailureNode(QObject *parent = 0);

Q_SIGNALS:
    void loopCountChanged(int value);
public:
    void setLoopCount(int value);
    int loopCount() const;
};

#endif // GREPEATUNTILFAILURENODE_P_H
