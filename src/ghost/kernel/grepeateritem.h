#ifndef GREPEATERITEM_H
#define GREPEATERITEM_H

#include "gdecoratoritem.h"

class GRepeaterItemPrivate;
class GRepeaterItem : public GDecoratorItem
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GRepeaterItem)
    Q_PROPERTY(int loopCount READ loopCount WRITE setLoopCount NOTIFY loopCountChanged)

public:
    explicit GRepeaterItem(QObject *parent = 0);

private:
    virtual Ghost::ItemType itemType() const Q_DECL_FINAL;

Q_SIGNALS:
    void loopCountChanged(int value);
public:
    void setLoopCount(int value);
    int loopCount() const;
};

#endif // GREPEATERITEM_H
