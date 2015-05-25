#ifndef GACTIONITEM_P_H
#define GACTIONITEM_P_H

#include "gghostitem_p.h"
#include "gactionitem.h"

class GActionItemPrivate : public GGhostItemPrivate
{
    Q_DECLARE_PUBLIC(GActionItem)

public:
    GActionItemPrivate();
    virtual ~GActionItemPrivate();

public:
    virtual bool initialize() Q_DECL_FINAL;

public:
    virtual void reset() Q_DECL_FINAL;
    virtual void execute() Q_DECL_FINAL;
    virtual void terminate() Q_DECL_FINAL;
};

#endif // GACTIONITEM_P_H
