#include "gghostdata_p.h"
#include "gghostdata_p_p.h"

// class GGhostData

GGhostData::GGhostData(QObject *parent)
    : QObject(*new GGhostDataPrivate(), parent)
{
}

void GGhostData::reset()
{
    Q_D(GGhostData);
    d->values.clear();
}

void GGhostData::set(const QString &key, const QJSValue &value)
{
    Q_D(GGhostData);

    if (value.isUndefined()) {
        d->values.remove(key);
    } else {
        d->values.insert(key, value);
    }
}

QJSValue GGhostData::get(const QString &key) const
{
    Q_D(const GGhostData);
    return d->values.value(key);
}

// class GGhostDataPrivate

GGhostDataPrivate::GGhostDataPrivate()
{
}

GGhostDataPrivate::~GGhostDataPrivate()
{
}
