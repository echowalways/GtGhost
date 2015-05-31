#ifndef GTIMEOUTNODE_P_H
#define GTIMEOUTNODE_P_H

#include "gleafnode_p.h"

class GTimeoutNodePrivate;
class GTimeoutNode : public GLeafNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GTimeoutNode)
    Q_PROPERTY(int duration READ duration WRITE setDuration NOTIFY durationChanged)

public:
    explicit GTimeoutNode(QObject *parent = 0);

Q_SIGNALS:
    void durationChanged(int value);
public:
    void setDuration(int value);
    int duration() const;

Q_SIGNALS:
    void started();
    void finished();
    void timeout();
public Q_SLOTS:
    void finish();

private:
    Q_PRIVATE_SLOT(d_func(), void onTimeout())
};

#endif // GTIMEOUTNODE_P_H
