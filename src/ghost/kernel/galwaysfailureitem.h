#ifndef GALWAYSFAILUREITEM_H
#define GALWAYSFAILUREITEM_H

#include "gdecoratoritem.h"

class GAlwaysFailureItemPrivate;
class GAlwaysFailureItem : public GDecoratorItem
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GAlwaysFailureItem)

public:
    explicit GAlwaysFailureItem(QObject *parent = 0);
};

#endif // GALWAYSFAILUREITEM_H
