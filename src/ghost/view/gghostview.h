#ifndef GGHOSTVIEW_H
#define GGHOSTVIEW_H

#include <QtQuick/QQuickItem>
#include <QtQml/QQmlComponent>

class GGhostTree;
class GGhostItem;

class GGhostViewPrivate;
class GGhostView : public QQuickItem
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GGhostView)
    Q_PROPERTY(QObject* target READ target WRITE setTarget NOTIFY targetChanged)
    Q_PROPERTY(QQmlComponent* itemDelegate READ itemDelegate WRITE setItemDelegate NOTIFY itemDelegateChanged)
    Q_PROPERTY(QQmlComponent* lineDelegate READ lineDelegate WRITE setLineDelegate NOTIFY lineDelegateChanged)

public:
    explicit GGhostView(QQuickItem *parent = 0);

private:
    virtual void classBegin() Q_DECL_FINAL;
    virtual void componentComplete() Q_DECL_FINAL;

Q_SIGNALS:
    void targetChanged(QObject *value);
    void itemDelegateChanged(QQmlComponent *value);
    void lineDelegateChanged(QQmlComponent *value);
public:
    void setTarget(QObject *value);
    void setItemDelegate(QQmlComponent *value);
    void setLineDelegate(QQmlComponent *value);
    QObject *target() const;
    QQmlComponent *itemDelegate() const;
    QQmlComponent *lineDelegate() const;
};

#endif // GGHOSTVIEW_H
