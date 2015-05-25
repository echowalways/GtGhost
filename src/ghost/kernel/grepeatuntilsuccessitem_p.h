#ifndef GREPEATUNTILSUCCESSITEM_P_H
#define GREPEATUNTILSUCCESSITEM_P_H

#include "gdecoratoritem_p.h"
#include "grepeatuntilsuccessitem.h"

class GRepeatUntilSuccessItemPrivate : public GDecoratorItemPrivate
{
    Q_DECLARE_PUBLIC(GRepeatUntilSuccessItem)

public:
    GRepeatUntilSuccessItemPrivate();
    virtual ~GRepeatUntilSuccessItemPrivate();

public:
    virtual void onChildStatusChanged(GGhostItem *child, Ghost::Status status) Q_DECL_FINAL;

public:
    virtual void executeChildItem() Q_DECL_FINAL;

public:
    int loopCount;
    int loopCounter;
};

#endif // GREPEATUNTILSUCCESSITEM_P_H
