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
    Q_PROPERTY(Ghost::Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(QString summarize READ summarize WRITE setSummarize NOTIFY summarizeChanged)
    Q_PRIVATE_PROPERTY(d_func(), QQmlListProperty<GGhostItem> childItems READ ghostItems CONSTANT DESIGNABLE false)
    Q_CLASSINFO("DefaultProperty", "childItems")
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
    void summarizeChanged(const QString &value);
public:
    void setSummarize(const QString &value);
    QString summarize() const;

};

#endif // GGHOSTNODE_H
