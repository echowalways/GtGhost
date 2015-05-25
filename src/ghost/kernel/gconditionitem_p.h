#ifndef GCONDITIONITEM_P_H
#define GCONDITIONITEM_P_H

#include "gghostitem_p.h"
#include "gconditionitem.h"

class GConditionItemPrivate : public GGhostItemPrivate
{
    Q_DECLARE_PUBLIC(GConditionItem)

public:
    GConditionItemPrivate();
    virtual ~GConditionItemPrivate();

public:
    virtual bool initialize() Q_DECL_FINAL;

public:
    virtual void reset() Q_DECL_FINAL;
    virtual void execute() Q_DECL_FINAL;
    virtual void terminate() Q_DECL_FINAL;

private:
    QJSValue condition;

public:
    bool callCondition();
};


#endif // GCONDITIONITEM_P_H
