#ifndef GDECORATORNODE_P_H
#define GDECORATORNODE_P_H

#include "gghostnode_p.h"

class GDecoratorNodePrivate;
class GDecoratorNode : public GGhostNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GDecoratorNode)
    Q_PROPERTY(Ghost::Status breakStatus READ breakStatus WRITE setBreakStatus NOTIFY breakStatusChanged)

protected:
    GDecoratorNode(GDecoratorNodePrivate &dd, QObject *parent);

Q_SIGNALS:
    void breakStatusChanged(Ghost::Status value);
public:
    void setBreakStatus(Ghost::Status value);
    Ghost::Status breakStatus() const;
};

#endif // GDECORATORNODE_P_H
