#include "testengine.h"

#include <QtCore>
#include <QtQml>
#include <QtTest>

TestEngine::TestEngine()
{
    QString imports = qApp->applicationDirPath() % QLatin1Literal("/../qml");
    this->addImportPath(imports);
}

TestEngine::~TestEngine()
{
}

void TestEngine::exec(const QString &fileName)
{
    QEventLoop ev;
    connect(this, SIGNAL(quit()),
            &ev, SLOT(quit()));

    QQmlComponent component(this);
    connect(&component, SIGNAL(statusChanged(QQmlComponent::Status)),
            this, SLOT(onStatusChanged()));
    component.loadUrl(fileName);

    ev.exec();

    QVERIFY(!component.isError());
}

void TestEngine::onStatusChanged()
{
    QQmlComponent *component
            = qobject_cast<QQmlComponent *>(QObject::sender());
    if (component->status() == QQmlComponent::Ready) {
        QObject *obj = component->create();
        Q_UNUSED(obj);
    } else if (component->isError()) {
        qDebug() << component->errorString();
    }
}

