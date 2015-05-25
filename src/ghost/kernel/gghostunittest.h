#ifndef GGHOSTUNITTEST_H
#define GGHOSTUNITTEST_H

#include <QtCore/QObject>
#include <QtQml/QQmlParserStatus>

#include "gghostnode.h"
#include "gghosttree.h"
#include "gghostitem.h"

class GGhostUnitTestPrivate;
class GGhostUnitTest : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GGhostUnitTest)
    Q_PRIVATE_PROPERTY(GGhostUnitTest::d_func(), QQmlListProperty<GGhostTree> ghostTrees READ ghostTrees DESIGNABLE false)
    Q_CLASSINFO("DefaultProperty", "ghostTrees")
    Q_INTERFACES(QQmlParserStatus)

public:
    explicit GGhostUnitTest(QObject *parent = 0);

private:
    virtual void classBegin() Q_DECL_FINAL;
    virtual void componentComplete() Q_DECL_FINAL;

public:
    Q_INVOKABLE void addStatus(QObject *object, Ghost::Status status);
private Q_SLOTS:
    void onStatusChanged(Ghost::Status status);
};

#endif // GGHOSTUNITTEST_H
