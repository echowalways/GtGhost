#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QString imports = app.applicationDirPath() + QLatin1Literal("/../qml");
    engine.addImportPath(imports);

    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}
