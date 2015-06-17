#ifndef GDECORATORNODE_P_H
#define GDECORATORNODE_P_H

#include "gghostnode_p.h"

class GDecoratorNodePrivate;
class GDecoratorNode : public GGhostNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GDecoratorNode)
    Q_PROPERTY(Ghost::Status brokenStatus READ brokenStatus WRITE setBrokenStatus NOTIFY brokenStatusChanged)

protected:
    GDecoratorNode(GDecoratorNodePrivate &dd, QObject *parent);

Q_SIGNALS:
    void brokenStatusChanged(Ghost::Status value);
public:
    void setBrokenStatus(Ghost::Status value);
    Ghost::Status brokenStatus() const;
};

#endif // GDECORATORNODE_P_H
