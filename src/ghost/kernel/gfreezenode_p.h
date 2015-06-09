#ifndef GFREEZENODE_P_H
#define GFREEZENODE_P_H

#include "gleafnode_p.h"

class GFreezeNodePrivate;
class GFreezeNode : public GLeafNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GFreezeNode)
    Q_PROPERTY(int duration READ duration WRITE setDuration NOTIFY durationChanged)

public:
    explicit GFreezeNode(QObject *parent = 0);

Q_SIGNALS:
    void durationChanged(int value);
public:
    void setDuration(int value);
    int duration() const;

Q_SIGNALS:
    void started();
    void finished();

private:
    void onTimeout();
    void onStatusChanged(Ghost::Status);
};

#endif // GFREEZENODE_P_H
