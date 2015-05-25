#ifndef GTGHOST_PLUGIN_H
#define GTGHOST_PLUGIN_H

#include <QQmlExtensionPlugin>

class GtGhostPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-devs.Gt.Ghost")

public:
    virtual void registerTypes(const char *uri) Q_DECL_FINAL;
};

#endif // GTGHOST_PLUGIN_H

