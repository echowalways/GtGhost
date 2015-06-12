#ifndef GGHOSTINSPECTOR_P_H
#define GGHOSTINSPECTOR_P_H

#include "gghostglobal.h"
#include "gghosttree_p.h"

class GGhostInspectorPrivate;
class GGhostInspector : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GGhostInspector)
    Q_PROPERTY(GGhostTree* target READ target WRITE setTarget NOTIFY targetChanged)
    Q_INTERFACES(QQmlParserStatus)

public:
    explicit GGhostInspector(QObject *parent = 0);

private:
    virtual void classBegin() Q_DECL_FINAL;
    virtual void componentComplete() Q_DECL_FINAL;

Q_SIGNALS:
    void targetChanged(GGhostTree *value);
private:
    void setTarget(GGhostTree *value);
    GGhostTree *target() const;
};

#endif // GGHOSTINSPECTOR_P_H
