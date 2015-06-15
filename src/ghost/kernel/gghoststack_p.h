#ifndef GGHOSTSTACK_P_H
#define GGHOSTSTACK_P_H

#include "gghostglobal.h"

class GGhostStackPrivate;
class GGhostStack : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GGhostStack)

private:
    explicit GGhostStack(QObject *parent = 0);
public:
    static GGhostStack *instance();

public:
    void push(GGhostTree *tree);
    void pop(GGhostTree *tree);
    GGhostTree *current() const;
};

#define theGhostStack GGhostStack::instance()

#endif // GGHOSTSTACK_P_H
