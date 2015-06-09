#ifndef GFREEZENODE_P_P_H
#define GFREEZENODE_P_P_H

#include <QtCore/QTimer>

#include "gleafnode_p_p.h"
#include "gfreezenode_p.h"

class GFreezeNodePrivate : GLeafNodePrivate
{
    Q_DECLARE_PUBLIC(GFreezeNode)

public:
    GFreezeNodePrivate();
    virtual ~GFreezeNodePrivate();

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

#endif // GFREEZENODE_P_P_H
