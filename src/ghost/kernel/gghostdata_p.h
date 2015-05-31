#ifndef GGHOSTDATA_H
#define GGHOSTDATA_H

#include <QtCore/QObject>
#include <QtQml/QJSValue>

class GGhostDataPrivate;
class GGhostData : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GGhostData)

public:
    explicit GGhostData(QObject *parent = 0);

public:
    void reset();

public:
    Q_INVOKABLE void set(const QString &key, const QJSValue &value);
    Q_INVOKABLE QJSValue get(const QString &key) const;

};

#endif // GGHOSTDATA_H
