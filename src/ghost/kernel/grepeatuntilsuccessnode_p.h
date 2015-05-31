#ifndef GREPEATUNTILSUCCESSNODE_P_H
#define GREPEATUNTILSUCCESSNODE_P_H

#include "gdecoratornode_p.h"

class GRepeatUntilSuccessNodePrivate;
class GRepeatUntilSuccessNode : public GDecoratorNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GRepeatUntilSuccessNode)
    Q_PROPERTY(int loopCount READ loopCount WRITE setLoopCount NOTIFY loopCountChanged)

public:
    explicit GRepeatUntilSuccessNode(QObject *parent = 0);

Q_SIGNALS:
    void loopCountChanged(int value);
public:
    void setLoopCount(int value);
    int loopCount() const;
};

#endif // GREPEATUNTILSUCCESSNODE_P_H
