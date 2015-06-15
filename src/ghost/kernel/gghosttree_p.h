#ifndef GGHOSTTREE_P_H
#define GGHOSTTREE_P_H

#include "gghostglobal.h"

class GBlackboard;

class GGhostTreePrivate;
class GGhostTree : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GGhostTree)
    Q_PROPERTY(Ghost::Status status READ status NOTIFY statusChanged)
    Q_PRIVATE_PROPERTY(d_func(), QQmlListProperty<GGhostNode> childNodes READ _q_childNodes CONSTANT DESIGNABLE false)
    Q_CLASSINFO("DefaultProperty", "childNodes")
    Q_INTERFACES(QQmlParserStatus)

public:
    explicit GGhostTree(QObject *parent = 0);

Q_SIGNALS:
    void statusChanged(Ghost::Status);
public:
    Ghost::Status status() const;

Q_SIGNALS:
    void initialized();
public:
    GGhostNodeList childNodes() const;

Q_SIGNALS:
    void started();
    void finished();
    void stopped();
public Q_SLOTS:
    void start();
    void stop();
    void reset();

private:
    virtual void classBegin() Q_DECL_FINAL;
    virtual void componentComplete() Q_DECL_FINAL;
};

#endif // GGHOSTTREE_P_H
