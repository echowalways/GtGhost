#ifndef GACTIONNODE_P_H
#define GACTIONNODE_P_H

#include "gleafnode_p.h"

class GActionNodePrivate;
class GActionNode : public GLeafNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GActionNode)
    Q_PROPERTY(int duration READ duration WRITE setDuration NOTIFY durationChanged)

public:
    explicit GActionNode(QObject *parent = 0);

Q_SIGNALS:
    void durationChanged(int value);
public:
    void setDuration(int value);
    int duration() const;

Q_SIGNALS:
    void reset();
    void execute();
    void terminate();

public Q_SLOTS:
    void setSuccess();
    void setFailure();
};

#endif // GACTIONNODE_P_H
