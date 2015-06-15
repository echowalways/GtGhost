#include "gghoststack_p.h"
#include "gghoststack_p_p.h"

#include <QtCore/QThreadStorage>

QThreadStorage<GGhostStack *> g_ghostStacks;

// class GGhostStack

GGhostStack::GGhostStack(QObject *parent)
    : QObject(*new GGhostStackPrivate(), parent)
{
}

GGhostStack *GGhostStack::instance()
{
    GGhostStack *ghostStack
            = g_ghostStacks.localData();

    if (nullptr == ghostStack) {
        ghostStack = new GGhostStack();
        g_ghostStacks.setLocalData(ghostStack);
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
