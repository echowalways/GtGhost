#include "gghoststack_p.h"
#include "gghoststack_p_p.h"

namespace GtGhostPrivate
{
QThreadStorage<GGhostStack *> ghostStacks;
}

// class GGhostStack

GGhostStack::GGhostStack(QObject *parent)
    : QObject(*new GGhostStackPrivate(), parent)
{
}

GGhostStack *GGhostStack::instance()
{
    using namespace GtGhostPrivate;

    GGhostStack *ghostStack
            = ghostStacks.localData();

    if (nullptr == ghostStack) {
        ghostStack = new GGhostStack();
        ghostStacks.setLocalData(ghostStack);
    }

    return ghostStack;
}

void GGhostStack::push(GGhostTree *tree)
{
    Q_D(GGhostStack);
    d->stack.push(tree);
}

void GGhostStack::pop(GGhostTree *tree)
{
    Q_D(GGhostStack);
    if (d->stack.pop() != tree) {
        Q_ASSERT(false);
    }
}

GGhostTree *GGhostStack::current() const
{
    Q_D(const GGhostStack);
    return d->stack.last();
}

// class GGhostStackPrivate

GGhostStackPrivate::GGhostStackPrivate()
{
}

GGhostStackPrivate::~GGhostStackPrivate()
{
}
