#ifndef GGHOSTINSPECTOR_P_P_H
#define GGHOSTINSPECTOR_P_P_H

#include <private/qobject_p.h>

#include "gghostinspector_p.h"

class GGhostInspectorPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(GGhostInspector)

public:
    GGhostInspectorPrivate();
    virtual ~GGhostInspectorPrivate();

public:
    QPointer<GGhostTree> target;
};

#endif // GGHOSTINSPECTOR_P_P_H

