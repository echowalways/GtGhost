#ifndef GREPEATUNTILFAILUREITEM_H
#define GREPEATUNTILFAILUREITEM_H

#include "gdecoratoritem.h"

class GRepeatUntilFailureItemPrivate;
class GRepeatUntilFailureItem : public GDecoratorItem
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GRepeatUntilFailureItem)
    Q_PROPERTY(int loopCount READ loopCount WRITE setLoopCount NOTIFY loopCountChanged)

public:
    explicit GRepeatUntilFailureItem(QObject *parent = 0);

private:
    virtual Ghost::ItemType itemType() const Q_DECL_FINAL;

Q_SIGNALS:
    void loopCountChanged(int value);
public:
    void setLoopCount(int value);
    int loopCount() const;
};

#endif // GREPEATUNTILFAILUREITEM_H
