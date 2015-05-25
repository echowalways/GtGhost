#ifndef GREPEATUNTILSUCCESSITEM_H
#define GREPEATUNTILSUCCESSITEM_H

#include "gdecoratoritem.h"

class GRepeatUntilSuccessItemPrivate;
class GRepeatUntilSuccessItem : public GDecoratorItem
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GRepeatUntilSuccessItem)
    Q_PROPERTY(int loopCount READ loopCount WRITE setLoopCount NOTIFY loopCountChanged)

public:
    explicit GRepeatUntilSuccessItem(QObject *parent = 0);

Q_SIGNALS:
    void loopCountChanged(int value);
public:
    void setLoopCount(int value);
    int loopCount() const;
};

#endif // GREPEATUNTILSUCCESSITEM_H
