#ifndef TESTENGINE_H
#define TESTENGINE_H

#include <QtQml/QQmlEngine>

class TestEngine : public QQmlEngine
{
    Q_OBJECT

public:
    TestEngine();
    virtual ~TestEngine();

public:
    void exec(const QString &fileName);
private Q_SLOTS:
    void onStatusChanged();
};

#endif // TESTENGINE_H
