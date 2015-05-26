#include "gghostunittest.h"
#include "gghostunittest_p.h"

#include <QtTest/QtTest>

#include "gghostnode_p.h"

// class GGhostUnitTest

GGhostUnitTest::GGhostUnitTest(QObject *parent)
    : QObject(*new GGhostUnitTestPrivate(), parent)
{
}

void GGhostUnitTest::classBegin()
{
}

void GGhostUnitTest::componentComplete()
{
    Q_D(GGhostUnitTest);

    if (d->childTrees.count() != 1) {
        QFAIL("Allows only one ghost tree.");
    }

    QStack<GGhostNode *> s;
    s.push(d->childTrees.at(0));

    while (!s.isEmpty()) {
        GGhostNode *n = s.pop();

        connect(n, SIGNAL(statusChanged(Ghost::Status)),
                this, SLOT(onStatusChanged(Ghost::Status)));

        Q_FOREACH (GGhostItem *c, n->childItems()) {
            s.push(c);
        }
    }
}

void GGhostUnitTest::addStatus(QObject *object, Ghost::Status status)
{
    Q_D(GGhostUnitTest);

    GGhostNode *node = qobject_cast<GGhostNode *>(object);
    if (!node) {
        QFAIL("Allows only GGhostNode type.");
    }

    d->expectedStatusNodes.append(node);
    d->expectedStatusValues.append(status);
}

void GGhostUnitTest::onStatusChanged(Ghost::Status status)
{
    Q_D(GGhostUnitTest);

    GGhostNode *node = qobject_cast<GGhostNode *>(QObject::sender());

    if (node->summarize().isEmpty()) {
        qDebug() << GGhostNodePrivate::toString(status) << node->metaObject()->className();
    } else {
        qDebug() << GGhostNodePrivate::toString(status) << node->summarize().toUtf8().constData();
    }

    if (d->expectedStatusNodes.isEmpty()) {
        qDebug() << "unexpected object: " << node->summarize().toUtf8().constData();
        QVERIFY(!d->expectedStatusNodes.isEmpty());
    } else {
        GGhostNode *expectedNode = d->expectedStatusNodes.takeFirst();
        if (expectedNode != node) {
            qDebug() << "\n  expected: " << expectedNode->summarize().toUtf8().constData()
                     << "\n  but  got: " << node->summarize().toUtf8().constData();
        }
        QVERIFY(expectedNode == node);
    }

    if (d->expectedStatusValues.isEmpty()) {
        qDebug() << "unexpected object: " << node->summarize().toUtf8().constData();
        QVERIFY(!d->expectedStatusValues.isEmpty());
    } else {
        Ghost::Status expectedStatus = d->expectedStatusValues.takeFirst();
        if (expectedStatus != status) {
            qDebug() << "object: " << node->summarize().toUtf8().constData()
                     << "\n  expected: " << GGhostNodePrivate::toString(expectedStatus)
                     << "\n  but  got: " << GGhostNodePrivate::toString(status);
        }
        QVERIFY(expectedStatus == status);
    }
}

// class GGhostUnitTestPrivate

GGhostUnitTestPrivate::GGhostUnitTestPrivate()
{
}

GGhostUnitTestPrivate::~GGhostUnitTestPrivate()
{
}

QQmlListProperty<GGhostTree> GGhostUnitTestPrivate::ghostTrees()
{
    return QQmlListProperty<GGhostTree>(q_func(), childTrees);
}

// moc_gghostunittest.cpp
#include "moc_gghostunittest.cpp"
