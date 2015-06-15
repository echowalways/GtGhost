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

public:
    Q_INVOKABLE void reset();
    Q_INVOKABLE int count() const;
    Q_INVOKABLE void clear();

public:
    Q_INVOKABLE bool done() const;
private:
    void onObjectStatusChanged(Ghost::Status status);
public:
    Q_INVOKABLE bool nextStatus(QObject *object, Ghost::Status status);
};

#endif // GGHOSTINSPECTOR_P_H
