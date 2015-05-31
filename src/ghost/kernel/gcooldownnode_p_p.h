#ifndef GCOOLDOWNNODE_P_P_H
#define GCOOLDOWNNODE_P_P_H

#include <QtCore/QTimer>

#include "gleafnode_p_p.h"
#include "gcooldownnode_p.h"

class GCooldownNodePrivate : GLeafNodePrivate
{
    Q_DECLARE_PUBLIC(GCooldownNode)

public:
    GCooldownNodePrivate();
    virtual ~GCooldownNodePrivate();

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

#endif // GCOOLDOWNNODE_P_P_H
