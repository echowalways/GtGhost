#include <QtCore>
#include <QtQml>
#include <QtTest>

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
    QVERIFY2(true, "Failure");
}

QTEST_MAIN(ItemsTest)

#include "tst_itemstest.moc"
