#ifndef GBLACKBOARD_P_H
#define GBLACKBOARD_P_H

#include "gghostglobal.h"

class GBlackboardAttached;

class GBlackboardPrivate;
class GBlackboard : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GBlackboard)

public:
    explicit GBlackboard(QObject *parent = 0);

public:
    Q_INVOKABLE void clear();
    Q_INVOKABLE bool has(const QString &key) const;
    Q_INVOKABLE void set(const QString &key, const QJSValue &value);
    Q_INVOKABLE QJSValue get(const QString &key) const;

public:
    static GBlackboardAttached *qmlAttachedProperties(QObject *target);
protected:
    explicit GBlackboard(GBlackboardPrivate &dd, QObject *parent = 0);
};

QML_DECLARE_TYPEINFO(GBlackboard, QML_HAS_ATTACHED_PROPERTIES)

class GBlackboardAttachedPrivate;
class GBlackboardAttached : public GBlackboard
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GBlackboardAttached)

public:
    explicit GBlackboardAttached(QObject *parent = 0);

public:
    Q_INVOKABLE void clearg();
    Q_INVOKABLE bool hasg(const QString &key) const;
    Q_INVOKABLE void setg(const QString &key, const QJSValue &value);
    Q_INVOKABLE QJSValue getg(const QString &key) const;

    Q_INVOKABLE void cleart();
    Q_INVOKABLE bool hast(const QString &key) const;
    Q_INVOKABLE void sett(const QString &key, const QJSValue &value);
    Q_INVOKABLE QJSValue gett(const QString &key) const;
};

#endif // GBLACKBOARD_P_H
