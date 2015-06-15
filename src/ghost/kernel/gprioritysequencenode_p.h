#ifndef GPRIORITYSEQUENCENODE_P_H
#define GPRIORITYSEQUENCENODE_P_H

#include "gcompositenode_p.h"

class GPrioritySequenceNodePrivate;
class GPrioritySequenceNode : public GCompositeNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GPrioritySequenceNode)
    Q_PROPERTY(Ghost::UpdateMode updateMode READ updateMode WRITE setUpdateMode NOTIFY updateModeChanged)

public:
    explicit GPrioritySequenceNode(QObject *parent = 0);

Q_SIGNALS:
    void updateModeChanged(Ghost::UpdateMode value);
public:
    void setUpdateMode(Ghost::UpdateMode value);
    Ghost::UpdateMode updateMode() const;

private:
    virtual void componentComplete() Q_DECL_FINAL;
};

#endif // GPRIORITYSEQUENCENODE_P_H
