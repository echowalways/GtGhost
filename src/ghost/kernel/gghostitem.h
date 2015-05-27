#ifndef GGHOSTITEM_H
#define GGHOSTITEM_H

#include <QtQml/QJSValue>

#include "gghostnode.h"

class GGhostItemPrivate;
class GGhostItem : public GGhostNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GGhostItem)
    Q_PROPERTY(Ghost::NodeType nodeType READ nodeType CONSTANT)
    Q_PROPERTY(Ghost::ItemType itemType READ itemType CONSTANT)
    Q_PROPERTY(GGhostTree *parentTree READ parentTree CONSTANT)
    Q_PROPERTY(GGhostItem *parentItem READ parentItem CONSTANT)
    Q_PROPERTY(QJSValue precondition READ precondition WRITE setPrecondition NOTIFY preconditionChanged)
    Q_PROPERTY(QJSValue weight READ weight WRITE setWeight NOTIFY weightChanged)

protected:
    GGhostItem(GGhostItemPrivate &dd, QObject *parent);

private:
    virtual void classBegin() Q_DECL_FINAL;
    virtual void componentComplete() Q_DECL_FINAL;

public:
    virtual Ghost::NodeType nodeType() const = 0;
    virtual Ghost::ItemType itemType() const = 0;

public:
    GGhostTree *parentTree() const;
    GGhostItem *parentItem() const;

Q_SIGNALS:
    void preconditionChanged(const QJSValue &value);
    void weightChanged(const QJSValue &value);
public:
    void setPrecondition(const QJSValue &value);
    void setWeight(const QJSValue &value);
    QJSValue precondition() const;
    QJSValue weight() const;

public:
    Q_INVOKABLE void set(const QString &key, const QJSValue &value);
    Q_INVOKABLE QJSValue get(const QString &key) const;
};

#endif // GGHOSTITEM_H
