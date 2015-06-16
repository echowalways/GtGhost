#ifndef GBLACKBOARD_P_H
#define GBLACKBOARD_P_H

#include "gghostglobal.h"

class GBlackboardPrivate;
class GBlackboard : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GBlackboard)
    Q_PROPERTY(GBlackboard* global READ globalBlackboard CONSTANT)
    Q_PROPERTY(GBlackboard* shared READ sharedBlackboard CONSTANT)

public:
    explicit GBlackboard(QObject *parent = 0);
public:
    static GBlackboard *qmlAttachedProperties(QObject *target);

public:
    GBlackboard *globalBlackboard() const;
    GBlackboard *sharedBlackboard() const;

public:
    Q_INVOKABLE bool has(const QString &key) const;
    Q_INVOKABLE void set(const QString &key, const QJSValue &value);
    Q_INVOKABLE QJSValue get(const QString &key) const;
    Q_INVOKABLE void unset(const QString &key);
    Q_INVOKABLE void clear();
};

QML_DECLARE_TYPEINFO(GBlackboard, QML_HAS_ATTACHED_PROPERTIES)

#endif // GBLACKBOARD_P_H
