#ifndef GRANDOMSELECTORNODE_P_H
#define GRANDOMSELECTORNODE_P_H

#include "gcompositenode_p.h"

class GRandomSelectorNodePrivate;
class GRandomSelectorNode : public GCompositeNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GRandomSelectorNode)
    Q_PROPERTY(Ghost::UpdateMode updateMode READ updateMode WRITE setUpdateMode NOTIFY updateModeChanged)
    Q_PROPERTY(Ghost::RandomMode randomMode READ randomMode WRITE setRandomMode NOTIFY randomModeChanged)

public:
    explicit GRandomSelectorNode(QObject *parent = 0);

Q_SIGNALS:
    void updateModeChanged(Ghost::UpdateMode value);
    void randomModeChanged(Ghost::RandomMode value);
public:
    void setUpdateMode(Ghost::UpdateMode value);
    void setRandomMode(Ghost::RandomMode value);
    Ghost::UpdateMode updateMode() const;
    Ghost::RandomMode randomMode() const;

private:
    virtual void componentComplete() Q_DECL_FINAL;
};

#endif // GRANDOMSELECTORNODE_P_H
