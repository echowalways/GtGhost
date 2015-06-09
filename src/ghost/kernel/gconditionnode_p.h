#ifndef GCONDITIONNODE_H
#define GCONDITIONNODE_H

#include "gleafnode_p.h"

class GConditionNodePrivate;
class GConditionNode : public GLeafNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GConditionNode)
    Q_PROPERTY(QJSValue condition READ condition WRITE setCondition NOTIFY conditionChanged)

public:
    explicit GConditionNode(QObject *parent = 0);

Q_SIGNALS:
    void conditionChanged(const QJSValue &value);
public:
    void setCondition(const QJSValue &value);
    QJSValue condition() const;

Q_SIGNALS:
    void passed();
    void unpassed();

private:
    void onStatusChanged(Ghost::Status);
};

#endif // GCONDITIONNODE_H
