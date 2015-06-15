#ifndef GGHOSTINSPECTOR_P_P_H
#define GGHOSTINSPECTOR_P_P_H

#include <private/qobject_p.h>

#include "gghostinspector_p.h"

typedef QPair<QObject *, Ghost::Status> ObjectStatus;

class GGhostInspectorPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(GGhostInspector)

public:
    GGhostInspectorPrivate();
    virtual ~GGhostInspectorPrivate();

public:
    QPointer<GGhostTree> target;
private:
    void connectObjects();
private:
    QList<ObjectStatus> statuses;
    int seek;
};

#endif // GGHOSTINSPECTOR_P_P_H

