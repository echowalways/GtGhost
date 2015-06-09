#ifndef GACTIONNODE_P_H
#define GACTIONNODE_P_H

#include "gleafnode_p.h"

class GActionNodePrivate;
class GActionNode : public GLeafNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GActionNode)
    Q_PROPERTY(int timeout READ timeout WRITE setTimeout NOTIFY timeoutChanged)

public:
    explicit GActionNode(QObject *parent = 0);

Q_SIGNALS:
    void reset();
    void execute();
    void terminate();

public Q_SLOTS:
    void setSuccessStatus();
    void setFailureStatus();
    void setStoppedStatus();

Q_SIGNALS:
    void timeoutChanged(int value);
public:
    void setTimeout(int value);
    int timeout() const;
};

#endif // GACTIONNODE_P_H
