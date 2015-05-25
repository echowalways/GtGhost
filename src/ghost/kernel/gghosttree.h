#ifndef GGHOSTTREE_H
#define GGHOSTTREE_H

#include <QtQml/QJSValue>

#include "gghostnode.h"

class GGhostTreePrivate;
class GGhostTree : public GGhostNode
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GGhostTree)

public:
    explicit GGhostTree(QObject *parent = 0);

private:
    virtual void classBegin() Q_DECL_FINAL;
    virtual void componentComplete() Q_DECL_FINAL;

public:
    Q_INVOKABLE void set(const QString &key, const QJSValue &value);
    Q_INVOKABLE QJSValue get(const QString &key) const;

Q_SIGNALS:
    void started();
    void finished();
    void stopped();

public Q_SLOTS:
    void start();
    void stop();
    void reset();
};

#endif // GGHOSTTREE_H
