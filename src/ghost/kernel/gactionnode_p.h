#ifndef GACTIONNODE_P_H
#define GACTIONNODE_P_H

#include "gleafnode_p.h"

class GActionNodePrivate;
class GActionNode : public GLeafNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GActionNode)

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
};

#endif // GACTIONNODE_P_H
