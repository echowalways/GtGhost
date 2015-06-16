#ifndef GDECORATORNODE_P_P_H
#define GDECORATORNODE_P_P_H

#include "gghostnode_p_p.h"
#include "gdecoratornode_p.h"

class GDecoratorNodePrivate : public GGhostNodePrivate
{
    Q_DECLARE_PUBLIC(GDecoratorNode)

public:
    explicit GDecoratorNodePrivate(Ghost::NodeType nodeType);
    virtual ~GDecoratorNodePrivate();

public:
    virtual bool reset() Q_DECL_FINAL;
    virtual void execute() Q_DECL_FINAL;
    virtual bool terminate() Q_DECL_FINAL;

public:
    Ghost::Status breakStatus;
};

#endif // GDECORATORNODE_P_P_H

