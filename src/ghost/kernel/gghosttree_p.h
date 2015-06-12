#ifndef GGHOSTTREE_P_H
#define GGHOSTTREE_P_H

#include <QtQml/QQmlParserStatus>

#include "gghostnamespace.h"

class GGhostTreePrivate;
class GGhostTree : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GGhostTree)
    Q_PROPERTY(Ghost::Status status READ status NOTIFY statusChanged)
    Q_PRIVATE_PROPERTY(d_func(), QQmlListProperty<GGhostNode> childNodes READ _q_childNodes CONSTANT DESIGNABLE false)
    Q_PRIVATE_PROPERTY(d_func(), GGhostData* Data READ _q_data CONSTANT)
    Q_INTERFACES(QQmlParserStatus)
    Q_CLASSINFO("DefaultProperty", "childNodes")

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

protected:
    virtual void classBegin() Q_DECL_OVERRIDE;
    virtual void componentComplete() Q_DECL_OVERRIDE;
};

#endif // GGHOSTTREE_P_H
