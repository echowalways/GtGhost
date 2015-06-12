#include "gghostinspector_p.h"
#include "gghostinspector_p_p.h"

// class GGhostInspector

GGhostInspector::GGhostInspector(QObject *parent)
    : QObject(*new GGhostInspectorPrivate(), parent)
{
}

void GGhostInspector::classBegin()
{
}

void GGhostInspector::componentComplete()
{
}

void GGhostInspector::setTarget(GGhostTree *value)
{
    Q_D(GGhostInspector);

    if (value != d->target) {
        d->target = value;
        emit targetChanged(value);
    }
}

GGhostTree *GGhostInspector::target() const
{
    Q_D(const GGhostInspector);
    return d->target.data();
}

// class GGhostInspectorPrivate

GGhostInspectorPrivate::GGhostInspectorPrivate()
{
}

GGhostInspectorPrivate::~GGhostInspectorPrivate()
{
}
