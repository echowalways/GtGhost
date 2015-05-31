#ifndef GCOOLDOWNNODE_P_H
#define GCOOLDOWNNODE_P_H

#include "gleafnode_p.h"

class GCooldownNodePrivate;
class GCooldownNode : public GLeafNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GCooldownNode)
    Q_PROPERTY(int duration READ duration WRITE setDuration NOTIFY durationChanged)

public:
    explicit GCooldownNode(QObject *parent = 0);

Q_SIGNALS:
    void durationChanged(int value);
public:
    void setDuration(int value);
    int duration() const;

Q_SIGNALS:
    void started();
    void finished();

private:
    Q_PRIVATE_SLOT(d_func(), void onTimeout())
};

#endif // GCOOLDOWNNODE_P_H
