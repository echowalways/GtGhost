#ifndef GGHOSTNODE_H
#define GGHOSTNODE_H

#include <QtCore/QObject>
#include <QtQml/QQmlParserStatus>

#include "gtghostnamespace.h"

class GGhostTree;
class GGhostItem;

typedef QList<GGhostItem *> GGhostItemList;

class GGhostNodePrivate;
class GGhostNode : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GGhostNode)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PRIVATE_PROPERTY(GGhostNode::d_func(), QQmlListProperty<GGhostItem> ghostItems READ ghostItems DESIGNABLE false)
    Q_CLASSINFO("DefaultProperty", "ghostItems")
    Q_INTERFACES(QQmlParserStatus)

protected:
    GGhostNode(GGhostNodePrivate &dd, QObject *parent);

public:
    GGhostItemList childItems() const;

Q_SIGNALS:
    void statusChanged(Ghost::Status status);
public:
    Ghost::Status status() const;

Q_SIGNALS:
    void descriptionChanged(const QString &value);
public:
    void setDescription(const QString &value);
    QString description() const;
};

#endif // GGHOSTNODE_H
