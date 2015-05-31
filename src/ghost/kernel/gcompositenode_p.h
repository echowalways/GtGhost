#ifndef GCOMPOSITENODE_P_H
#define GCOMPOSITENODE_P_H

#include "gghostnode_p.h"

class GCompositeNodePrivate;
class GCompositeNode : public GGhostNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GCompositeNode)
    Q_PROPERTY(Ghost::Status breakStatus READ breakStatus WRITE setBreakStatus NOTIFY breakStatusChanged)
    Q_PROPERTY(int unmatchCount READ unmatchCount WRITE setUnmatchCount NOTIFY unmatchCountChanged)

protected:
    GCompositeNode(GCompositeNodePrivate &dd, QObject *parent);

Q_SIGNALS:
    void breakStatusChanged(Ghost::Status value);
    void unmatchCountChanged(int value);
public:
    void setBreakStatus(Ghost::Status value);
    void setUnmatchCount(int value);
    Ghost::Status breakStatus() const;
    int unmatchCount() const;
};

#endif // GCOMPOSITENODE_P_H
