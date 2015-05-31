#ifndef GTIMEOUTNODE_P_P_H
#define GTIMEOUTNODE_P_P_H

#include <QtCore/QTimer>

#include "gleafnode_p_p.h"
#include "gtimeoutnode_p.h"

class GTimeoutNodePrivate : public GLeafNodePrivate
{
    Q_DECLARE_PUBLIC(GTimeoutNode)

public:
    GTimeoutNodePrivate();
    virtual ~GTimeoutNodePrivate();

protected:
    virtual void onStatusChanged(Ghost::Status status) Q_DECL_FINAL;

public:
    virtual void reset() Q_DECL_FINAL;
    virtual void execute() Q_DECL_FINAL;
    virtual void terminate() Q_DECL_FINAL;

public:
    int duration;
    QPointer<QTimer> timer;
private:
    void onTimeout();
};

#endif // GTIMEOUTNODE_P_P_H
