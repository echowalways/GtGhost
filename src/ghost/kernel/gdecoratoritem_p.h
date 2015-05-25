#ifndef GDECORATORITEM_P_H
#define GDECORATORITEM_P_H

#include "gghostitem_p.h"
#include "gdecoratoritem.h"

class GDecoratorItemPrivate : public GGhostItemPrivate
{
    Q_DECLARE_PUBLIC(GDecoratorItem)

public:
    GDecoratorItemPrivate();
    virtual ~GDecoratorItemPrivate();

public:
    virtual bool initialize() Q_DECL_FINAL;

public:
    virtual void reset() Q_DECL_FINAL;
    virtual void execute() Q_DECL_FINAL;
    virtual void terminate() Q_DECL_FINAL;

protected:
    void setSuccessIfPreconditionFalse();
    void setFailureIfPreconditionFalse();
protected:
    virtual void executeChildItem() = 0;
};

#endif // GDECORATORITEM_P_H
