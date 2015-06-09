#ifndef GCONDITIONNODE_P_P_H
#define GCONDITIONNODE_P_P_H

#include "gleafnode_p_p.h"
#include "gconditionnode_p.h"

class GConditionNodePrivate : public GLeafNodePrivate
{
    Q_DECLARE_PUBLIC(GConditionNode)

public:
    GConditionNodePrivate();
    virtual ~GConditionNodePrivate();

public:
    virtual void reset() Q_DECL_FINAL;
    virtual void execute() Q_DECL_FINAL;
    virtual void terminate() Q_DECL_FINAL;

public:
    bool callCondition();
private:
    QJSValue condition;

private:
    void onStatusChanged(Ghost::Status status);
};

#endif // GCONDITIONNODE_P_P_H

