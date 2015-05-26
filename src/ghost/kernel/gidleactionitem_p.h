#ifndef GIDLEACTIONITEM_P_H
#define GIDLEACTIONITEM_P_H

#include <QtCore/QTimer>

#include "gghostitem_p.h"
#include "gidleactionitem.h"

class GIdleActionItemPrivate : public GGhostItemPrivate
{
    Q_DECLARE_PUBLIC(GIdleActionItem)

public:
    GIdleActionItemPrivate();
    virtual ~GIdleActionItemPrivate();

public:
    virtual bool initialize() Q_DECL_FINAL;

public:
    virtual void reset() Q_DECL_FINAL;
    virtual void execute() Q_DECL_FINAL;
    virtual void terminate() Q_DECL_FINAL;

private:
    int duration;
    QPointer<QTimer> timer;
private:
    void onTimeout();
};

#endif // GIDLEACTIONITEM_P_H
