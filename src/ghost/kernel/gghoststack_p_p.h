#ifndef GGHOSTSTACK_P_P_H
#define GGHOSTSTACK_P_P_H

#include <private/qobject_p.h>

#include "gghoststack_p.h"

class GGhostStackPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(GGhostStack)

public:
    GGhostStackPrivate();
    virtual ~GGhostStackPrivate();

private:
    QStack<GGhostTree *> stack;
};

#endif // GGHOSTSTACK_P_P_H

