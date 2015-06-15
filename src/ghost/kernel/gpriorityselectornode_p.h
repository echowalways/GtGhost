#ifndef GPRIORITYSELECTORNODE_P_H
#define GPRIORITYSELECTORNODE_P_H

#include "gcompositenode_p.h"

class GPrioritySelectorNodePrivate;
class GPrioritySelectorNode : public GCompositeNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GPrioritySelectorNode)
    Q_PROPERTY(Ghost::UpdateMode updateMode READ updateMode WRITE setUpdateMode NOTIFY updateModeChanged)

public:
    explicit GPrioritySelectorNode(QObject *parent = 0);

Q_SIGNALS:
    void updateModeChanged(Ghost::UpdateMode value);
public:
    void setUpdateMode(Ghost::UpdateMode value);
    Ghost::UpdateMode updateMode() const;

private:
    virtual void componentComplete() Q_DECL_FINAL;
};

#endif // GPRIORITYSELECTORNODE_P_H
