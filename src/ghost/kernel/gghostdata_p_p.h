#ifndef GGHOSTDATA_P_P_H
#define GGHOSTDATA_P_P_H

#include <private/qobject_p.h>
#include "gghostdata_p.h"

class GGhostDataPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(GGhostData)

public:
    GGhostDataPrivate();
    virtual ~GGhostDataPrivate();

public:
    QHash<QString, QJSValue> values;
};

#endif // GGHOSTDATA_P_P_H

