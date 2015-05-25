#ifndef GCONDITIONITEM_H
#define GCONDITIONITEM_H

#include "gghostitem.h"

class GConditionItemPrivate;
class GConditionItem : public GGhostItem
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GConditionItem)
    Q_PROPERTY(QJSValue condition READ condition WRITE setCondition NOTIFY conditionChanged)

public:
    explicit GConditionItem(QObject *parent = 0);

Q_SIGNALS:
    void conditionChanged(const QJSValue &value);
public:
    void setCondition(const QJSValue &value);
    QJSValue condition() const;

Q_SIGNALS:
    void reset();
};

#endif // GCONDITIONITEM_H
