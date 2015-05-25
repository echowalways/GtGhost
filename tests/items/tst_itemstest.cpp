#include <QtCore>
#include <QtQml>
#include <QtTest>

#include "testengine.h"

class ItemsTest : public QObject
{
    Q_OBJECT

public:
    ItemsTest();

private Q_SLOTS:
    void testCase();
};

ItemsTest::ItemsTest()
{
}

void ItemsTest::testCase()
{
    TestEngine testEngine;
    testEngine.exec(QLatin1Literal("qrc:/SimpleGhostItems.qml"));
}

QTEST_MAIN(ItemsTest)

#include "tst_itemstest.moc"
